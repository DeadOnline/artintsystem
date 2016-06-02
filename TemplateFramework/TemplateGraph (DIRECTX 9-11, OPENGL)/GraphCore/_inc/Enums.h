#pragma once
#ifndef EnumsHeader
#define EnumsHeader

namespace GRAPHCORE
	{
	enum	CAMERA_TYPES { Free, Target };
	enum	COLLISION_TYPES { None, Map, Sphere, Box };
	enum	LIGHT_TYPES { Spotlight, Directed, Zonal, Parallel_Point, Dissiminated };
	enum	OBJECT_TYPES	{ Dummy, Static, Active };
	enum	BUFFER_CONTENT_TYPES { index, vertex };
	enum	VERTEX_TYPES { v2dcolor, v2dcolortex, v2dtex, v3dcolor, v3dcolornormal, v3dcolortex, v3dcolornormaltex, v3dnormal, v3dnormaltex, v3dtex };
	
	enum	GEOMETRY_TYPES { Cube, Ball, Plane, Vector };
	enum	TEXTURE_TYPES { Solid, Chess, Watermark };
	enum	MATERIAL_TYPES { Ambient, AmbientDiffuse, AmbientDiffuseSpecular, AmbientDiffuseSpecularEmittive };
	
	enum	RENDERER_TYPES { DirectX9, DirectX11, OpenGL };
	enum	DIRECTX_SUPPORTED_FILE_FORMATS { _x, _obj, _g };
	enum	SUPPORTED_FILE_FORMATS { _X };
	enum	DEFAULT_COLORS { White, Black };
	enum	ATTRIBUTES_TYPES { Geometry, Material, Texture, Normal, Animation };
	}

#endif // !EnumsHeader