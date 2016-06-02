#pragma once
#ifndef WorldPositionHeader
#define WorldPositionHeader

namespace GRAPHCORE
	{
	struct	WORLDPOSITION
		{
		private:
			float x, y, z, w, *x_binded, *y_binded, *z_binded, *w_binded;

		public:
			WORLDPOSITION( float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f );
			WORLDPOSITION( const WORLDPOSITION &_worldPosition );

			void InternalCopy( const WORLDPOSITION &_worldPosition );

			void operator=( const WORLDPOSITION &a );
			void operator+=( const WORLDPOSITION &a );
			void operator/=( const float _value );

			WORLDPOSITION operator*( const float _value );

			float &GetXBinded();
			float &GetYBinded();
			float &GetZBinded();
			float &GetWBinded();

			float GetXDefault();
			float GetYDefault();
			float GetZDefault();
			float GetWDefault();

			void SetXDefault( float _x );
			void SetYDefault( float _y );
			void SetZDefault( float _z );
			void SetWDefault( float _w );

			void SetXBinded( float &_x );
			void SetYBinded( float &_y );
			void SetZBinded( float &_z );
			void SetWBinded( float &_w );

			void UnbindCoords();
		};
	}

#endif