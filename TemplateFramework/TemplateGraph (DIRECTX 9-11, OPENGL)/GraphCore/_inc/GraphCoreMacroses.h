#pragma once
#ifndef GraphCoreMacrosesHeader
#define GraphCoreMacrosesHeader

#include <Windows.h>
#include <math.h>
#include "../../../TemplateCommon/CommonCore/Macroses.h"

namespace GRAPHCORE
	{
	#define CAMERA_STARTING_POS 10
	#define CREATE_ARRAY(arr, arrclass, arrsize) if (arrsize) arr = new arrclass[arrsize];

	#define MIN(A,B) (((A)<(B))?(A):(B))
	#define MAX(A,B) (((A)>(B))?(A):(B))
	#define VEC_SUB(R,A,B) {(R)[0]=(A)[0]-(B)[0];(R)[1]=(A)[1]-(B)[1]; \
		( R )[ 2 ] = ( A )[ 2 ] - ( B )[ 2 ]; }
	#define VEC_ADD(R,A,B) {(R)[0]=(A)[0]+(B)[0];(R)[1]=(A)[1]+(B)[1]; \
		( R )[ 2 ] = ( A )[ 2 ] + ( B )[ 2 ]; }
	#define VEC_MULN(A,N) { (A)[0]*=(N); (A)[1]*=(N); (A)[2]*=(N); }
	#define VEC_DIVV(R,A,B) {(R)[0]=(A)[0]/(B)[0];(R)[1]=(A)[1]/(B)[1]; \
		( R )[ 2 ] = ( A )[ 2 ] / ( B )[ 2 ]; }
	#define VEC_ASSIGN(A,B) {(A)[0]=(B)[0];(A)[1]=(B)[1];(A)[2]=(B)[2];}
	#define VEC_MIN(R,A,B){(R)[0] = MIN((A)[0],(B)[0]); \
		( R )[ 1 ] = MIN(( A )[ 1 ], ( B )[ 1 ]); \
		( R )[ 2 ] = MIN(( A )[ 2 ], ( B )[ 2 ]); }
	#define VEC_MAX(R,A,B){(R)[0] = MAX((A)[0],(B)[0]); \
		( R )[ 1 ] = MAX(( A )[ 1 ], ( B )[ 1 ]); \
		( R )[ 2 ] = MAX(( A )[ 2 ], ( B )[ 2 ]); }

	#define DEFAULT_MODEL "_default.x"
	#define DEFAULT_MATERIAL "_default.m"
	#define DEFAULT_TEXTURE "_default.png"

	#define PATH_MODEL "./GameCore/_res/_models/"
	#define PATH_MATERIAL "./GameCore/_res/_materials/"
	#define PATH_TEXTURES "./GameCore/_res/_textures/"

	#define DEFAULT_PATH_MODEL PATH_MODEL DEFAULT_MODEL
	#define DEFAULT_PATH_MATERIAL PATH_MATERIAL DEFAULT_MATERIAL
	#define DEFAULT_PATH_TEXTURE PATH_TEXTURES DEFAULT_TEXTURE

	#define GET_DEFAULT_PATH_MODEL(name) string(DEFAULT_PATH_MODEL).append(name).c_str()
	#define GET_DEFAULT_PATH_MATERIAL(name) (name==NULL)?DEFAULT_PATH_MATERIAL:string(PATH_MATERIAL).append(name).c_str()

	#define MAPNONEXISTANTID -1
	#define MAPDEFAULT 0	
	}

#endif