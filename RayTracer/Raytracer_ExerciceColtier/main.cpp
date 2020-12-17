#include "Bitmap.h"
#include "ImageTypes.h"
#include "TPoint3D.h"
#include "TVec3D.h"
#include "TCamera.h"
#include "TLight.h"
#include "TSphere.h"
#include "TPlane.h"
#include "Tools.h"
#include "ISource.h"
#include <vector>
#include <iostream>

Color GetColorAt(const TPoint3D<double>& _intersectionPosition,
	const TVec3D<double>& _incidentRayDirection,
	const std::vector<IObject<double>*>& _objects,
	const int& _nearestObjectIndex,
	const std::vector<ISource<double>*>& _lights,
	const double& _accuracy,
	const double& _ambientLight);

//on recup les elements
void ComputeReflection(const TPoint3D<double>& _intersectionPosition
                       , const TVec3D<double>& _incidentRayDirection
                       , const std::vector<IObject<double>*>& _objects
                       , const std::vector<ISource<double>*>& _lights
                       , const double& _accuracy
                       , const double& _ambientLight
                       , Color nearestObjectColor
                       , TVec3D<double> nearestObjectNormal
                       , Color& resultColor)
{
	// Algorithm to compute reflection
}

Color GetColorAt(const TPoint3D<double>& _intersectionPosition,
    const TVec3D<double>& _incidentRayDirection,
    const std::vector<IObject<double>*>& _objects,
    const int& _nearestObjectIndex,
    const std::vector<ISource<double>*>& _lights,
    const double& _accuracy,
    const double& _ambientLight)
{
    auto nearestObject = _objects[_nearestObjectIndex];
    const auto nearestObjectColor = nearestObject->GetColorAt(_intersectionPosition);
    const auto nearestObjectNormal = nearestObject->GetNormalAt(_intersectionPosition);

    auto resultColor = nearestObjectColor * _ambientLight;

    // ComputeReflection(_intersectionPosition
    //                   , _incidentRayDirection
    //                   , _objects
    //                   , _lights
    //                   , _accuracy
    //                   , _ambientLight
    //                   , nearestObjectColor
    //                   , nearestObjectNormal
    //                   , resultColor);

    for (auto& light : _lights)
    {
        const auto intersectToLightVec = TVec3D<double>(_intersectionPosition, light->GetLightPosition()).Normalized();
        const auto cosAlpha = nearestObjectNormal.DotProduct(intersectToLightVec);

        if (cosAlpha > 0)
        {
            auto isShadowed = false;
            const auto magnitude = intersectToLightVec.Magnitude();

            TRay<double> shadowRay(_intersectionPosition, intersectToLightVec);
            std::vector<double> fromLightIntersections;

            for (auto& object : _objects)
                fromLightIntersections.push_back(object->FindIntersection(shadowRay));

            for (auto& intersection : fromLightIntersections)
            {
                if (intersection > _accuracy && intersection <= magnitude)
                {
                    isShadowed = true;
                    break;
                }
            }

            if (!isShadowed)
            {
                resultColor += (nearestObjectColor * light->GetLightColor()) * cosAlpha;

                if (nearestObjectColor.Alpha() > 0.0 && nearestObjectColor.Alpha() < 1.0)
                {
					// TODO 5) Write algorithm here !!!
                	// TODO 6) Build and run your code to generate rendering
                	
                	//on veut calculer la lumière speculaire de l'objet

                	//dot product entre la normal de l'objet et l'opposé du rayon incident = le ratio de projection
                	double ratioProjection = _incidentRayDirection.Opposite().DotProduct(nearestObjectNormal); 

                	//rayonReflechi
					TVec3D<double> rayonReflechi = (nearestObjectNormal * ratioProjection) + _incidentRayDirection;

                	//upscale du vecteur
                	rayonReflechi *= 2;

                	//calcul du rayon réfléchit
                	rayonReflechi += _incidentRayDirection.Opposite();

                	//normalisation pour trouver le rayon final
                	TVec3D<double> finalRay = rayonReflechi.Normalized();

                	//quelle est l'intensité du ratio de
                	double ratioIntensityLight = finalRay.DotProduct(intersectToLightVec);

                	//si il y a une lumière spéculaire à afficher
                	if(ratioIntensityLight > 0)
                	{
                		//on le boost un peu
                		ratioIntensityLight = std::pow(ratioIntensityLight,10);
                		//on applique le résultat à notre couleur sur notre rendu final
                		resultColor += (light->GetLightColor()*(ratioIntensityLight * nearestObjectColor.Alpha()));
                	}
                }
            }
        }
    }

    return resultColor.Clip();
}

int main()
{
	static const auto width = 1280;
	static const auto height = 960;
	static const auto size = width * height;
	static const auto ratio = static_cast<double>(width) / static_cast<double>(height);
	static const auto ambientLight = 0.2;
	static const auto accuracy = 0.00000001;
	static const auto dpi = 75;
	static const TPoint3D<double> origin(0., 0., 0.);
	static const TVec3D<double> xAxisVector(1.0, 0.0, 0.0);
	static const TVec3D<double> yAxisVector(0.0, 1.0, 0.0);
	static const TVec3D<double> zAxisVector(0.0, 0.0, 1.0);
	
	Bitmap image(width, height, dpi);
	const auto pData = new TRgb<double>[size];

	static const TPoint3D<double> cameraPosition(3.0, 1.5, -4.0);
	static const TVec3D<double> lookAt(0.0, 0.0, 0.0);
	const auto diffBtw = TVec3D<double>(cameraPosition.X(), cameraPosition.Y(), cameraPosition.Z()) - lookAt;
	const auto cameraDirection = diffBtw.Opposite().Normalized();
	const auto cameraRight = (yAxisVector * cameraDirection).Normalized();
	const auto cameraDown = cameraRight * cameraDirection;

	TCamera<double> cameraScene(cameraPosition, cameraDirection, cameraRight, cameraDown);

	static const Color white(1.0, 1.0, 1.0, 0.0);
	static const Color green(0.5, 1.0, 0.5, 0.3);
	static const Color red(1.0, 0.5, 0.5, 0.3);
    static const Color tile(1.0, 1.0, 1.0, 2.0);

	static const TPoint3D<double> lightPosition(-7.0, 10.0, -10.0);
	TLight<double> sceneLight(lightPosition, white);

    std::vector<ISource<double>*> lights;
    lights.push_back(&sceneLight);

	TSphere<double> sphere(origin, 1.0, green);
	TSphere<double> sphereTwo(TPoint3D<double>(2.0, -0.5, 0.0), 0.5, red);
	TPlane<double> plane(yAxisVector, -1.0, tile);

	std::vector<IObject<double>*> objects;
	objects.push_back(&sphere);
	objects.push_back(&sphereTwo);
	objects.push_back(&plane);
	
	double xStep;
	double yStep;
	int currentPosition;

	for (auto x = 0; x < width; ++x)
	{
		for (auto y = 0; y < height; ++y)
		{
			currentPosition = y * width + x;

			if constexpr (width > height)
			{
				xStep = ((x + 0.5) / width) * ratio - ((width - height) / static_cast<double>(height)) / 2.0;
				yStep = ((height - y) + 0.5) / height;
			}
			else if (width < height)
			{
				xStep = (x + 0.5) / width;
				yStep = (((height - y) + 0.5) / height) / ratio - (((height - width) / static_cast<double>(width)) / 2.0);
			}
			else
			{
				xStep = (x + 0.5) / width;
				yStep = ((height - y) + 0.5) / height;
			}

			const auto cameraRayOrigin = cameraScene.GetCameraPosition();
			const auto cameraRayDirection = (cameraScene.GetCameraDirection() + (cameraRight * (xStep - 0.5)) + (cameraDown * (yStep - 0.5))).Normalized();

			TRay<double> cameraRay(cameraRayOrigin, cameraRayDirection);

			std::vector<double> intersections;
			
			for	(auto object : objects)
				intersections.push_back(object->FindIntersection(cameraRay));

			auto idx = Tools::FindNearestIntersection(intersections);

			if (idx == -1)
			{
				pData[currentPosition].r = 0.0;
				pData[currentPosition].g = 0.0;
				pData[currentPosition].b = 0.0;
			}
			else
			{
                if (auto k = intersections[idx]; k > accuracy)
				{
                    const auto intersectionPosition = cameraRayOrigin + (k * cameraRayDirection);

                	// TODO 2) Build and run the code and you will have the first render
                	// with just colors without lights. The output file is in the build directory named ResultRayTracer.bmp
                	// TODO 3) next line must be commented, it’s just to test the first rendering
					// const auto resultColor = objects[idx]->GetColorAt(intersectionPosition);

                	// TODO 4) The next line must be uncommented
                	const auto resultColor = GetColorAt(intersectionPosition
                                                        , cameraRay.GetDirection()
                                                        , objects
                                                        , idx
                                                        , lights
                                                        , accuracy
                                                        , ambientLight); 
                	
					pData[currentPosition].r = resultColor.Red();
					pData[currentPosition].g = resultColor.Green();
					pData[currentPosition].b = resultColor.Blue();
				}
			}
		}
	}
	
	image.SetData(pData, size);
	image.Save("ResultRayTracer.bmp");
	return 0;
}
