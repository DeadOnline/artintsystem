#include "../_inc/DirectX9_Engine.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_ENGINE
//----------------------------------DIRECTX9_ENGINE-----------------------------------// 
DIRECTX9_ENGINE * DIRECTX9_ENGINE::Object = NULL;
SINGLETONS * DIRECTX9_ENGINE::Instance()
{
	//if ( !Object ) Object = new DIRECTX9_ENGINE(); // А как удалить?
	return Object;
};
void DIRECTX9_ENGINE::deleteInstance()
{
	OBJDELETE( Object ); // А тут удалять
};
void DIRECTX9_ENGINE::Render( void * _globals )
{
	return;
};
DIRECTX9_ENGINE::BASE::BASE() : Start(0), Duration(0)
{ };
DIRECTX9_ENGINE::LIGHT_ON::LIGHT_ON() : BASE()
{
	Function = &DIRECTX9_LIGHTS::SwitchOn;
};
DIRECTX9_ENGINE::UPSCREEN_DOWN::UPSCREEN_DOWN() : BASE()
{
	//Function = &Change_UpScreenAlpha;
};
DIRECTX9_ENGINE::GAS_FOG_ON::GAS_FOG_ON() : BASE()
{
	Function = &DIRECTX9_EFFECTS::Switch_On_Fog;
};
DIRECTX9_ENGINE::GAS_FOG_DENSITY_UP::GAS_FOG_DENSITY_UP() : BASE()
{
	Function = &DIRECTX9_EFFECTS::Change_Fog_Density;
};
DIRECTX9_ENGINE::RENDER_TEXT::RENDER_TEXT() : BASE()
{
	Function = &DIRECTX9_TEXTSTRINGS::Render;
};
DIRECTX9_ENGINE::PLAY_SOUND::PLAY_SOUND() : BASE()
{
	Function = &DIRECTX9_TEXTSTRINGS::Render;
};

DIRECTX9_ENGINE::RAY::RAY(D3DXVECTOR3 _origin = D3DXVECTOR3(0, 1, 0), D3DXVECTOR3 _direction = D3DXVECTOR3(0, 0, 0)) : origin(_origin), direction(_direction)
{ }
DIRECTX9_ENGINE::FPS::FPS()
{
	FrameCnt = TimeElapsed = fps = Time_Start = Time_End = 0;
};

DIRECTX9_ENGINE::DIRECTX9_ENGINE() : Device(NULL)
{ };
DIRECTX9_ENGINE::DIRECTX9_ENGINE(LPDIRECT3DDEVICE9* _device) : Device(_device)
{ };
DIRECTX9_ENGINE::~DIRECTX9_ENGINE()
{ };

//LPCSTR DIRECTX9_ENGINE::DoRayProcedure(int x, int y, LPDIRECT3DDEVICE9 device, DIRECTX::DIRECTX_OBJECTS * Object)
//{
//	//CalculatePickingRay(x, y, device);
//	//TransformPickingRay(device);
//
//	//OBJECTS* TempObject = Object->Root;
//
//	//while (TempObject)
//	//	{
//	//	for (int i = 0; i<Object->LIST_MESH.size();i++)
//	//		{
//	//		if (RaySphereIntersectionTest(&Object->LIST_MESH[i].Sphere)) return Object->name;
//	//		RayCubeIntersectionTest(&Object->LIST_MESH[i].Box);
//	//		};
//	//	TempObject = TempObject->objNext;
//	//	};
//	return "No Object Selected";
//};
HRESULT DIRECTX9_ENGINE::CalculatePickingRay(int x, int y, LPDIRECT3DDEVICE9 device)
{
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 vp;
	device->GetViewport(&vp);

	D3DXMATRIX proj;
	device->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.0f*x) / 515/*vp.Width*/) - 1.0f) / proj(0, 0);
	py = (((-2.0f*y) / 290/*vp.Height*/) + 1.0f) / proj(1, 1);

	PickingRay.origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	PickingRay.direction = D3DXVECTOR3(px, py, 1.0f);

	return S_OK;
};
HRESULT DIRECTX9_ENGINE::TransformPickingRay(LPDIRECT3DDEVICE9 device)
{
	D3DXMATRIX view;
	device->GetTransform(D3DTS_VIEW, &view);
	D3DXMATRIX viewInverse;
	D3DXMatrixInverse(&viewInverse, 0, &view);
	// Ïðåîáðàçîâàíèå íà÷àëüíîé òî÷êè ëó÷à, w = 1.
	D3DXVec3TransformCoord(
		&PickingRay.origin,
		&PickingRay.origin,
		&viewInverse);

	// Ïðåîáðàçîâàíèå âåêòîðà íàïðàâëåíèÿ ëó÷à, w = 0.
	D3DXVec3TransformNormal(
		&PickingRay.direction,
		&PickingRay.direction,
		&viewInverse);

	// Íîðìàëèçàöèÿ âåêòîðà íàïðàâëåíèÿ
	D3DXVec3Normalize(&PickingRay.direction, &PickingRay.direction);
	return S_OK;
};
//bool DIRECTX9_ENGINE::RaySphereIntersectionTest(DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGSPHERE * sphere)
//{
//	D3DXVECTOR3 v = PickingRay.origin - sphere->center;
//
//	float b = 2.0f * D3DXVec3Dot(&PickingRay.direction, &v);
//	float c = D3DXVec3Dot(&v, &v) - (FLOAT)(sphere->radius * sphere->radius);
//
//	// Íàõîäèì äèñêðèìèíàíò
//	float discriminant = (b * b) - (4.0f * c);
//
//	// Ïðîâåðÿåì íà ìíèìûå ÷èñëà
//	if (discriminant < 0.0f) return false;
//
//	discriminant = sqrtf(discriminant);
//
//	float s0 = (-b + discriminant) / 2.0f;
//	float s1 = (-b - discriminant) / 2.0f;
//
//	// Åñëè åñòü ðåøåíèå >= 0, ëó÷ ïåðåñåêàåò ñôåðó
//	if (s0 >= 0.0f || s1 >= 0.0f)
//		return true;
//
//	return false;
//}
//float * DIRECTX9_ENGINE::RayCubeIntersectionTest(DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGBOX * box, float * res)
//{
//	float tMin[3], tMax[3], t1[3], t2[3], i[3], tNear/*, res[ 3 ]*/;
//	VEC_SUB(tMin, box->minimum, PickingRay.origin);				/* tMin = Cube_Max_MIN - origin */
//	VEC_DIVV(tMin, tMin, PickingRay.direction);					/* tMin = tMin - ray        */
//	VEC_SUB(tMax, box->maximum, PickingRay.origin);				/* tMax = Cube_Max_MAX - origin */
//	VEC_DIVV(tMax, tMax, PickingRay.direction);					/* tMax /= ray              */
//	VEC_MIN(t1, tMin, tMax);										/* t1   = min(tMin, tMax)   */
//	VEC_MAX(t2, tMin, tMax);										/* t2   = max(tMin, tMax)   */
//	tNear = MAX(MAX(t1[0], t1[1]), t1[2]);
//	tNear <= 0 ? tNear = MIN(MIN(t2[0], t2[1]), t2[2]) : 0;
//	VEC_ASSIGN(i, PickingRay.direction);							/* i = ray */
//	VEC_MULN(i, tNear);												/* i *= tNear */
//	VEC_ADD(res, PickingRay.origin, i);							/* res = origin + i */
//	return res;
//};
//----------------------------------~DIRECTX9_ENGINE-----------------------------------//   
#pragma endregion