#include <stdio.h>
#include <xmmintrin.h>
#include <stdlib.h>
#include <math.h>

void compute_arrays( float pA[], float pB[], float pC[], size_t sz )
{
  float m1, m2, m3, m4;
  for ( size_t i = 0; i < sz; i++ )
  {
    m1 = pA[i] * pA[i];         // m1 = pA[i] * pB[i] (element-wise multiplication)
    m2 = pB[i] * pB[i];         // m2 = pA[
    m3 = m1 + m2;
    m4 = m1 - m2;
    m4 = sqrt( m4 );
    pC[i] = m4 + 0.5;
  }
}

void compute_arrays_sse( float pA[], float pB[], float pC[], size_t sz )
{
    size_t N = sz / 4;

    __m128 m1, m2, m3, m4;

    __m128* pSrcA = (__m128*) pA;
    __m128* pSrcB = (__m128*) pB;
    __m128* pDest = (__m128*) pC;

    __m128 m0_5 = _mm_set_ps1(0.5f);        // m0_5[0, 1, 2, 3] = 0.5

    for ( int i = 0; i < N; i++ )
    {
      m1 = _mm_mul_ps(pSrcA[i], pSrcA[i]);        // m1 = pSrcA[i] * pSrcA[i]
      m2 = _mm_mul_ps(pSrcB[i], pSrcB[i]);        // m2 = pSrcB[i] * pSrcB[i]
      m3 = _mm_add_ps(m1, m2);                    // m3 = m1 + m2
      m4 = _mm_sub_ps(m1, m2);                    // m4 = m1 - m2
      m4 = _mm_sqrt_ps(m4);
      pDest[i] = _mm_add_ps(m4, m0_5);            // pDest[i] = m4 + 0.5
    }
}

int main( int argc, char ** argv )
{
  size_t vector_size, n_recomputes;
  float chksum = 0;

  if ( argc != 3 )
  {
    printf( "Usage: %s <array-size> <number-of-recomputations>\n", argv[0] );
    return 1;
  }
  else
  {
    sscanf(argv[1], "%lu", &vector_size );
    sscanf(argv[2], "%lu", &n_recomputes );
  }

  float * X = (float*)malloc( vector_size * sizeof( float ) );
  float * Y = (float*)malloc( vector_size * sizeof( float ) );
  float * Z = (float*)malloc( vector_size * sizeof( float ) );

  for ( size_t i = 0; i < vector_size ; i++ )
  {
    X[i] = (float)i;
    Y[i] = (float)i;
  }
  
#ifdef USE_SSE
  printf("Using SSE...\n");
  for ( size_t i = 0; i < n_recomputes; i++ )
  {
    compute_arrays_sse( X, Y, Z, vector_size );
  }
#else
  printf("Not Using SSE...\n");
  for ( size_t i = 0; i < n_recomputes; i++ )
  {
    compute_arrays( X, Y, Z, vector_size );
  }
#endif

  for ( size_t i = 0; i < vector_size ; i++ )
  {
    chksum += Z[i];
  }

  printf("Checksum: %f\n", chksum);

  free(X);
  free(Y);
  free(Z);

  return 0;
}
