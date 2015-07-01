#version 120

// ---> Shadertoy uniforms
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform float function;
uniform bool multiply_by_F1;
uniform bool multiply_by_F2;

uniform bool inverse;
uniform float distance_type;
uniform bool bwSwitch;


//uniform vec4 iMouse;
//uniform sampler2D iChannel0; // Texture #1
//uniform sampler2D iChannel1; // Texture #2
//uniform sampler2D iChannel2; // Texture #3
//uniform sampler2D iChannel3; // Texture #4
//uniform vec4 iDate;



// Voronoi noises
// by Pietro De Nicola
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.


#define SCALE		   10.0		// 3.0
#define BIAS   		   +0.0
#define POWER			1.0		
#define OCTAVES   		4		// 7
#define SWITCH_TIME 	5.0		// seconds
#define WARP_INTENSITY	0.00	// 0.06
#define WARP_FREQUENCY	16.0

float t = iGlobalTime/SWITCH_TIME;

//
// the following parameters identify the voronoi you're watching
// and will change automatically
//
//float function 			= mod(t,4.0);
//bool  multiply_by_F1	= mod(t,8.0)  >= 4.0;
//bool  inverse			= mod(t,16.0) >= 8.0;
//float distance_type		= mod(t/16.0,4.0);




//------------------------------------------------------------
// printing helper
// https://www.shadertoy.com/view/4sBSWW

float DigitBin(const in int x)
{
    return x==0?480599.0:x==1?139810.0:x==2?476951.0:x==3?476999.0:x==4?350020.0:x==5?464711.0:x==6?464727.0:x==7?476228.0:x==8?481111.0:x==9?481095.0:0.0;
}

float PrintValue(const in vec2 fragCoord, const in vec2 vPixelCoords, const in vec2 vFontSize, const in float fValue, const in float fMaxDigits, const in float fDecimalPlaces)
{
    vec2 vStringCharCoords = (fragCoord.xy - vPixelCoords) / vFontSize;
    if ((vStringCharCoords.y < 0.0) || (vStringCharCoords.y >= 1.0)) return 0.0;
	float fLog10Value = log2(abs(fValue)) / log2(10.0);
	float fBiggestIndex = max(floor(fLog10Value), 0.0);
	float fDigitIndex = fMaxDigits - floor(vStringCharCoords.x);
	float fCharBin = 0.0;
	if(fDigitIndex > (-fDecimalPlaces - 1.01)) {
		if(fDigitIndex > fBiggestIndex) {
			if((fValue < 0.0) && (fDigitIndex < (fBiggestIndex+1.5))) fCharBin = 1792.0;
		} else {		
			if(fDigitIndex == -1.0) {
				if(fDecimalPlaces > 0.0) fCharBin = 2.0;
			} else {
				if(fDigitIndex < 0.0) fDigitIndex += 1.0;
				float fDigitValue = (abs(fValue / (pow(10.0, fDigitIndex))));
                float kFix = 0.0001;
                fCharBin = DigitBin(int(floor(mod(kFix+fDigitValue, 10.0))));
			}		
		}
	}
    return floor(mod((fCharBin / pow(2.0, floor(fract(vStringCharCoords.x) * 4.0) + (floor(vStringCharCoords.y * 5.0) * 4.0))), 2.0));
}
//------------------------------------------------------------




//
// Noise functions
//

vec2 hash( vec2 p )
{
    p = vec2( dot(p,vec2(127.1,311.7)), dot(p,vec2(269.5,183.3)) );
	return fract(sin(p)*43758.5453);
}

float noise( in vec2 p )
{
    vec2 i = floor( p );
    vec2 f = fract( p );
	
	vec2 u = f*f*(3.0-2.0*f);

    return mix( mix( dot( hash( i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ), 
                     dot( hash( i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                mix( dot( hash( i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ), 
                     dot( hash( i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

float voronoi( in vec2 x )
{
    vec2 n = floor( x );
    vec2 f = fract( x );

	float F1 = 8.0;
	float F2 = 8.0;
	
	
    for( int j=-1; j<=1; j++ )
    for( int i=-1; i<=1; i++ )
    {
        vec2 g = vec2(i,j);
        vec2 o = hash( n + g );

        o = 0.5 + 0.41*sin( iGlobalTime + 6.2831*o ); // animate

		vec2 r = g - f + o;

		float d = 	distance_type < 1.0 ? dot(r,r)  :				// euclidean^2
				  	distance_type < 2.0 ? sqrt(dot(r,r)) :			// euclidean
					distance_type < 3.0 ? abs(r.x) + abs(r.y) :		// manhattan
					distance_type < 4.0 ? max(abs(r.x), abs(r.y)) :	// chebyshev
					0.0;

		if( d<F1 ) 
		{ 
			F2 = F1; 
			F1 = d; 
		}
		else if( d<F2 ) 
		{
			F2 = d;
		}
    }
	
	float c = function < 1.0 ? F1 : 
			  function < 2.0 ? F2 : 
			  function < 3.0 ? F2-F1 :
			  function < 4.0 ? (F1+F2)/2.0 : 
			  0.0;
		
	if( multiply_by_F1 )	c *= F1;
    if( multiply_by_F2 )	c *= F2;
	if( inverse )			c = 1.0 - c;
	
    return c;
}

float fbm( in vec2 p )
{
	float s = 0.0;
	float m = 0.0;
	float a = 0.5;
	
	for( int i=0; i<OCTAVES; i++ )
	{
		s += a * voronoi(p);
		m += a;
		a *= 0.5;
		p *= 2.0;
	}
	return s/m;
}

//
// Main
//

void main( )//out vec4 fragColor, in vec2 fragCoord )
{

    vec2 p = gl_FragCoord.xy/iResolution.xx;
	float w = noise( p * WARP_FREQUENCY );
	p += WARP_INTENSITY * vec2(w,-w);
    float c = POWER*fbm( SCALE*p ) + BIAS;
    float a = c;
    if (bwSwitch) c = 1.0-c;
    vec3 color = c * vec3( 0.4, 1.0, 0.9 );
    
    // print t
   // vec2 fontsize = vec2(8.0, 15.0);
   // vec2 position = vec2(0.0, 0.0);
   // float prn = PrintValue(gl_FragCoord.xy, position + vec2(0.0, 6.0), fontsize, t, 1.0, 0.0);
   // color = mix( color, vec3(0.7, 0.0, 0.0), prn);
	
    //fragColor = vec4( color, 1.0 );
    gl_FragColor = vec4( color, a );
}