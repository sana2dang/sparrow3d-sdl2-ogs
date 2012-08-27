/*
 The contents of this file are subject to the Mozilla Public License
 Version 1.1 (the "License"); you may not use this file except in
 compliance with the License. You may obtain a copy of the License at
 http://www.mozilla.org/MPL/

 Software distributed under the License is distributed on an "AS IS"
 basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 License for the specific language governing rights and limitations
 under the License.

 Alternatively, the contents of this file may be used under the terms
 of the GNU Lesser General Public license (the  "LGPL License"), in which case the
 provisions of LGPL License are applicable instead of those
 above.

 For feedback and questions about my Files and Projects please mail me,
 Alexander Matthes (Ziz) , zizsdl_at_googlemail.com
*/

/* This file is very bad style - and I know it! But this is the best
 * way to get the code fast and still understanable. The only
 * alternative I used before was massive copy and paste, which is
 * bollocks. */

#ifdef __SPARROW_INTERNAL_ZBOTH__
	#ifdef __GNUC__
	inline void draw_line_ztest_zset( Sint32 x1, Sint32 z1, Sint32 x2, Sint32 z2, Sint32 y, Uint32 color, Sint32 sZ ) __attribute__((always_inline));
	#endif
	inline void draw_line_ztest_zset( Sint32 x1, Sint32 z1, Sint32 x2, Sint32 z2, Sint32 y, Uint32 color, Sint32 sZ )
#elif defined __SPARROW_INTERNAL_ZTEST__
	#ifdef __GNUC__
	inline void draw_line_ztest( Sint32 x1, Sint32 z1, Sint32 x2, Sint32 z2, Sint32 y, Uint32 color, Sint32 sZ ) __attribute__((always_inline));
	#endif
	inline void draw_line_ztest( Sint32 x1, Sint32 z1, Sint32 x2, Sint32 z2, Sint32 y, Uint32 color, Sint32 sZ )
#elif defined __SPARROW_INTERNAL_ZSET__
	#ifdef __GNUC__
	inline void draw_line_zset( Sint32 x1, Sint32 z1, Sint32 x2, Sint32 z2, Sint32 y, Uint32 color, Sint32 sZ ) __attribute__((always_inline));
	#endif
	inline void draw_line_zset( Sint32 x1, Sint32 z1, Sint32 x2, Sint32 z2, Sint32 y, Uint32 color, Sint32 sZ )
#else
	#ifdef __GNUC__
	inline void draw_line( Sint32 x1, Sint32 x2, Sint32 y, Uint32 color ) __attribute__((always_inline));
	#endif
	inline void draw_line( Sint32 x1, Sint32 x2, Sint32 y, Uint32 color )
#endif
{
	if ( x1 >= spTargetX )
		return;
	if ( x2 < 0 )
		return;
	#ifndef __SPARROW_INTERNAL_ZNOTHING__
		Sint32 z = z1;
	#endif
	if ( x1 < 0 )
	{
		#ifndef __SPARROW_INTERNAL_ZNOTHING__
			z -= x1 * sZ;
		#endif
		x1 = 0;
	}
	if ( x2 >= spTargetX )
		x2 = spTargetX - 1;
	#ifdef __SPARROW_INTERNAL_ZNOTHING__
		spHorizentalLine( spTargetPixel, x1, y, x2 - x1, color, 1, spTargetX, spTargetY );
	#else
		int x;
		for ( x = x1; x <= x2; x++ )
		{
			#ifdef __SPARROW_INTERNAL_ZBOTH__
				draw_pixel_ztest_zset( x, y, z, color )
			#elif defined __SPARROW_INTERNAL_ZTEST__
				draw_pixel_ztest( x, y, z, color )
			#elif defined __SPARROW_INTERNAL_ZSET__
				draw_pixel_zset( x, y, z, color )
			#endif
				z += sZ;
		}
	#endif
}

#ifdef __SPARROW_INTERNAL_ZBOTH__
	inline void sp_intern_Triangle_ztest_zset( Sint32 x1, Sint32 y1, Sint32 z1, Sint32 x2, Sint32 y2, Sint32 z2, Sint32 x3, Sint32 y3, Sint32 z3, Uint32 color )
#elif defined __SPARROW_INTERNAL_ZTEST__
	inline void sp_intern_Triangle_ztest( Sint32 x1, Sint32 y1, Sint32 z1,   Sint32 x2, Sint32 y2, Sint32 z2,   Sint32 x3, Sint32 y3, Sint32 z3,   Uint32 color )
#elif defined __SPARROW_INTERNAL_ZSET__	
	inline void sp_intern_Triangle_zset( Sint32 x1, Sint32 y1, Sint32 z1,   Sint32 x2, Sint32 y2, Sint32 z2,   Sint32 x3, Sint32 y3, Sint32 z3,   Uint32 color )
#else
	inline void sp_intern_Triangle( Sint32 x1, Sint32 y1, Sint32 z1,   Sint32 x2, Sint32 y2, Sint32 z2,   Sint32 x3, Sint32 y3, Sint32 z3,   Uint32 color )
#endif
{
	int y;
	if ( y2 < 0 )
		return;
	if ( y1 >= spTargetY )
		return;
	SDL_LockSurface( spTarget );

	Sint32 x4 = x1;
	Sint32 y4 = y1;
	#ifndef __SPARROW_INTERNAL_ZNOTHING__
		Sint32 z4 = z1;
	#endif
	int div = y2 - y1;
	if ( div != 0 )
	{
		int mul = y3 - y1;
		Sint32 mul32 = mul * one_over_x( div ); //(mul<<SP_PRIM_ACCURACY)/div;
		x4 = x1 + ( ( x2 - x1 ) * mul32 >> SP_PRIM_ACCURACY );
		y4 = y3;
		//z4 = z1+((z2-z1)*mul32>>SP_PRIM_ACCURACY-SP_ACCURACY);
		#ifndef __SPARROW_INTERNAL_ZNOTHING__
			z4 = z1 + mul * z_div( z2 - z1, div );
		#endif
	}
	Sint32 xl = x1 << SP_PRIM_ACCURACY;
	#ifndef __SPARROW_INTERNAL_ZNOTHING__
		Sint32 zl = z1;
	#endif
	Sint32 sX_l = 0;
	Sint32 sZ_l = 0;
	if ( ( y1 - y2 ) != 0 )
	{
		Sint32 mul = one_over_x( y1 - y2 ); //(1<<SP_PRIM_ACCURACY)/(y1-y2);
		sX_l = ( x1 - x2 ) * mul;
		//sZ_l = (z1-z2)*mul;
		#ifndef __SPARROW_INTERNAL_ZNOTHING__
			sZ_l = z_div( z1 - z2, y1 - y2 );
		#endif
	}

	Sint32 xr = xl;
	Sint32 sX_r = 0;
	#ifndef __SPARROW_INTERNAL_ZNOTHING__
		Sint32 zr = zl;
		Sint32 sZ_r = 0;
	#endif
	if ( ( y1 - y3 ) != 0 )
	{
		Sint32 mul = one_over_x( y1 - y3 ); //(1<<SP_PRIM_ACCURACY)/(y1-y3);
		sX_r = ( x1 - x3 ) * mul;
		//sZ_r = (z1-z3)*mul;
		#ifndef __SPARROW_INTERNAL_ZNOTHING__
			sZ_r = z_div( z1 - z3, y1 - y3 );
		#endif
	}

	if ( y3 < 0 )
	{
		int diff = y3 - y1;
		xl += sX_l * diff;
		xr += sX_r * diff;
		#ifndef __SPARROW_INTERNAL_ZNOTHING__
			zl += sZ_l * diff;
			zr += sZ_r * diff;
		#endif
	}
	else
	{
		if ( y1 < 0 )
		{
			int diff = -y1;
			y1 = 0;
			xl += sX_l * diff;
			xr += sX_r * diff;
			#ifndef __SPARROW_INTERNAL_ZNOTHING__
				zl += sZ_l * diff;
				zr += sZ_r * diff;
			#endif
		}
		if ( y3 >= spTargetY )
			y3 = spTargetY - 1;

		#ifndef __SPARROW_INTERNAL_ZNOTHING__
			Sint32 sZ = 0;		
			if ( ( x4 - x3 ) != 0 )
			{
				//Sint32 mul = one_over_x(x4-x3);//(1<<SP_PRIM_ACCURACY)/(x4-x3);
				//sZ = (z4-z3)*mul;
				sZ = z_div( z4 - z3, x4 - x3 );
			}
		#endif
		if ( x4 < x3 )
		{
			for ( y = y1; y < y3; y++ )
			{
				//if ((xl-xr>>SP_PRIM_ACCURACY)!=0)
				//  sZ = z_div(zl-zr,xl-xr>>SP_PRIM_ACCURACY);
				#ifdef __SPARROW_INTERNAL_ZBOTH__
					draw_line_ztest_zset( xl >> SP_PRIM_ACCURACY, zl,
					                      xr >> SP_PRIM_ACCURACY, zr, y, color, sZ );
				#elif defined __SPARROW_INTERNAL_ZTEST__
					draw_line_ztest( xl >> SP_PRIM_ACCURACY, zl,
					                 xr >> SP_PRIM_ACCURACY, zr, y, color, sZ );
				#elif defined __SPARROW_INTERNAL_ZSET__	
					draw_line_zset( xl >> SP_PRIM_ACCURACY, zl,
					                xr >> SP_PRIM_ACCURACY, zr, y, color, sZ );
				#else
					draw_line( xl >> SP_PRIM_ACCURACY, 
					           xr >> SP_PRIM_ACCURACY, y, color);
				#endif
				xl += sX_l;
				xr += sX_r;
				#ifndef __SPARROW_INTERNAL_ZNOTHING__
					zl += sZ_l;
					zr += sZ_r;
				#endif
			}
		}
		else
		{
			#ifndef __SPARROW_INTERNAL_ZNOTHING__
				Sint32 sZ = 0;
				if ( ( x4 - x3 ) != 0 )
				{
					//Sint32 mul = one_over_x(x4-x3);//(1<<SP_PRIM_ACCURACY)/(x4-x3);
					//sZ = (z4-z3)*mul;
					sZ = z_div( z4 - z3, x4 - x3 );
				}
			#endif
			for ( y = y1; y < y3; y++ )
			{
				//if ((xl-xr>>SP_PRIM_ACCURACY)!=0)
				//  sZ = z_div(zl-zr,xl-xr>>SP_PRIM_ACCURACY);
				#ifdef __SPARROW_INTERNAL_ZBOTH__
					draw_line_ztest_zset( xr >> SP_PRIM_ACCURACY, zr,
					                      xl >> SP_PRIM_ACCURACY, zl, y, color, sZ );
				#elif defined __SPARROW_INTERNAL_ZTEST__
					draw_line_ztest( xr >> SP_PRIM_ACCURACY, zr,
					                 xl >> SP_PRIM_ACCURACY, zl, y, color, sZ );
				#elif defined __SPARROW_INTERNAL_ZSET__	
					draw_line_zset( xr >> SP_PRIM_ACCURACY, zr,
					                xl >> SP_PRIM_ACCURACY, zl, y, color, sZ );
				#else
					draw_line( xr >> SP_PRIM_ACCURACY, 
					           xl >> SP_PRIM_ACCURACY, y, color);
				#endif
				xl += sX_l;
				xr += sX_r;
				#ifndef __SPARROW_INTERNAL_ZNOTHING__
					zl += sZ_l;
					zr += sZ_r;
				#endif
			}
		}
	}

	xr = x3 << SP_PRIM_ACCURACY;
	sX_r = 0;
	#ifndef __SPARROW_INTERNAL_ZNOTHING__
		zr = z3;
		sZ_r = 0;
	#endif
	if ( ( y2 - y3 ) != 0 )
	{
		Sint32 mul = one_over_x( y2 - y3 ); //(1<<SP_PRIM_ACCURACY)/(y2-y3);
		sX_r = ( x2 - x3 ) * mul;
		//sZ_r = (z2-z3)*mul;
		#ifndef __SPARROW_INTERNAL_ZNOTHING__
			sZ_r = z_div( z2 - z3, y2 - y3 );
		#endif
	}

	if ( y3 < 0 )
	{
		int diff = -y3;
		y3 = 0;
		xl += sX_l * diff;
		xr += sX_r * diff;
		#ifndef __SPARROW_INTERNAL_ZNOTHING__
			zl += sZ_l * diff;
			zr += sZ_r * diff;
		#endif
	}
	if ( y2 >= spTargetY )
		y2 = spTargetY - 1;

	#ifndef __SPARROW_INTERNAL_ZNOTHING__
		Sint32 sZ = 0;
		if ( ( x4 - x3 ) != 0 )
		{
			//Sint32 mul = one_over_x(x4-x3);//(1<<SP_PRIM_ACCURACY)/(x4-x3);
			//sZ = (z4-z3)*mul;
			sZ = z_div( z4 - z3, x4 - x3 );
		}
	#endif
	if ( x4 < x3 )
	{
		for ( y = y3; y <= y2; y++ )
		{
			//if ((xl-xr>>SP_PRIM_ACCURACY)!=0)
			//  sZ = z_div(zl-zr,xl-xr>>SP_PRIM_ACCURACY);
			#ifdef __SPARROW_INTERNAL_ZBOTH__
				draw_line_ztest_zset( xl >> SP_PRIM_ACCURACY, zl,
									  xr >> SP_PRIM_ACCURACY, zr, y, color, sZ );
			#elif defined __SPARROW_INTERNAL_ZTEST__
				draw_line_ztest( xl >> SP_PRIM_ACCURACY, zl,
								 xr >> SP_PRIM_ACCURACY, zr, y, color, sZ );
			#elif defined __SPARROW_INTERNAL_ZSET__	
				draw_line_zset( xl >> SP_PRIM_ACCURACY, zl,
								xr >> SP_PRIM_ACCURACY, zr, y, color, sZ );
			#else
				draw_line( xl >> SP_PRIM_ACCURACY, 
						   xr >> SP_PRIM_ACCURACY, y, color);
			#endif
			xl += sX_l;
			xr += sX_r;
			#ifndef __SPARROW_INTERNAL_ZNOTHING__
				zl += sZ_l;
				zr += sZ_r;
			#endif
		}
	}
	else
	{
		#ifndef __SPARROW_INTERNAL_ZNOTHING__
			Sint32 sZ = 0;
			if ( ( x4 - x3 ) != 0 )
			{
				//Sint32 mul = one_over_x(x4-x3);//(1<<SP_PRIM_ACCURACY)/(x4-x3);
				//sZ = (z4-z3)*mul;
				sZ = z_div( z4 - z3, x4 - x3 );
			}
		#endif
		for ( y = y3; y <= y2; y++ )
		{
			//if ((xl-xr>>SP_PRIM_ACCURACY)!=0)
			//  sZ = z_div(zl-zr,xl-xr>>SP_PRIM_ACCURACY);
			#ifdef __SPARROW_INTERNAL_ZBOTH__
				draw_line_ztest_zset( xr >> SP_PRIM_ACCURACY, zr,
									  xl >> SP_PRIM_ACCURACY, zl, y, color, sZ );
			#elif defined __SPARROW_INTERNAL_ZTEST__
				draw_line_ztest( xr >> SP_PRIM_ACCURACY, zr,
								 xl >> SP_PRIM_ACCURACY, zl, y, color, sZ );
			#elif defined __SPARROW_INTERNAL_ZSET__	
				draw_line_zset( xr >> SP_PRIM_ACCURACY, zr,
								xl >> SP_PRIM_ACCURACY, zl, y, color, sZ );
			#else
				draw_line( xr >> SP_PRIM_ACCURACY, 
						   xl >> SP_PRIM_ACCURACY, y, color);
			#endif
			xl += sX_l;
			xr += sX_r;
			#ifndef __SPARROW_INTERNAL_ZNOTHING__
				zl += sZ_l;
				zr += sZ_r;
			#endif
		}
	}
	SDL_UnlockSurface( spTarget );
}
