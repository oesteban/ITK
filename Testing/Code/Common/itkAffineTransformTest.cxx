/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkAffineTransformTest.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/

#include <iostream>

#include "itkAffineTransform.h"

int
main(
    int argc,
    char *argv[])
{
    int any = 0;       // Any errors detected in testing?
    vnl_matrix_fixed<double,2,2> matrix2;
    vnl_matrix_fixed<double,2,2> inverse2;
    vnl_vector_fixed<double,2>   vector2;
    int i, j;

    /* FIXME: This code exercises most of the methods but doesn't
       actually check that the results are correct. */
    any = 0;
    std::cout << "The AffineTransform class is still being implemented"
              << std::endl;

    /* Create a 2D identity transformation and show its parameters */
    itk::AffineTransform<double,2> id2;
    matrix2 = id2.GetMatrix();
    vector2 = id2.GetOffset();
    std::cout << "Matrix from instantiating an identity transform:"
              << std::endl << matrix2;
    std::cout << "Vector from instantiating an identity transform:"
              << std::endl << vector2 << std::endl;

    /* Create and show a simple 2D transform from given parameters */
    matrix2[0][0] = 1;
    matrix2[0][1] = 2;
    matrix2[1][0] = 3;
    matrix2[1][1] = 4;
    vector2[0] = 5;
    vector2[1] = 6;
    itk::AffineTransform<double,2> aff2(matrix2, vector2);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            matrix2[i][j] = 0.0;
        vector2[i]    = 0.0;
    }
    std::cout << "Instantiation of a given 2D transform:" 
              << std::endl << aff2;
    inverse2 = aff2.GetInverse();
    std::cout << "Inverse matrix for the given transform:"
              << std::endl << inverse2;

    /* Set parameters of a 2D transform */
    matrix2[0][0] = 6;
    matrix2[0][1] = 5;
    matrix2[1][0] = 4;
    matrix2[1][1] = 3;
    vector2[0] = 2;
    vector2[1] = 1;
    aff2.SetMatrix(matrix2);
    aff2.SetOffset(vector2);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            matrix2[i][j] = 0.0;
        vector2[i]    = 0.0;
    }
    matrix2 = aff2.GetMatrix();
    vector2 = aff2.GetOffset();
    std::cout << "Setting the matrix in an existing transform:"
              << std::endl << matrix2;
    std::cout << "Setting the offset in an existing  transform:"
              << std::endl << vector2 << std::endl;

    /* Try composition of two transformations */
    aff2.Compose(aff2);
    std::cout << "Result of a composition:"
              << std::endl << aff2;

    /* Compose with a translation */
    vnl_vector_fixed<double, 2> trans;
    trans[0] = 1;
    trans[1] = 2;
    aff2.Translate(trans);
    std::cout << "Result of a translation:"
              << std::endl << aff2;

    /* Compose with an isotropic scaling */
    aff2.Scale(.3, 1);
    std::cout << "Result of isotropic scaling:"
              << std::endl << aff2;

    /* Compose with an anisotropic scaling */
    vnl_vector_fixed<double, 2> scale;
    scale[0] = .3;
    scale[1] = .2;
    aff2.Scale(scale);
    std::cout << "Result of anisotropic scaling:"
              << std::endl << aff2;

    /* Compose with a general N-D rotation */
    aff2.Rotate(0, 1, 0.57, 1);
    std::cout << "Result of general rotation:"
              << std::endl << aff2;

    /* Compose with a 2-D rotation */
    aff2.Rotate(0, 1, -0.57, 1);
    std::cout << "Result of 2-D rotation:"
              << std::endl << aff2;

    /* Compose with a shear */
    aff2.Shear(1, 0, .2);
    std::cout << "Result of shear:"
              << std::endl << aff2;

    /* Transform a point */
    itk::Point<2, double> u2, v2;
    u2[0] = 3;
    u2[1] = 5;
    v2 = aff2.Transform(u2);
    std::cout << "Transform a point:" << std::endl
              << v2 << std::endl;

    /* Back transform a point */
    v2 = aff2.BackTransform(u2);
    std::cout << "Back transform a point:" << std::endl
              << v2 << std::endl;

    /* Transform a vector */
    vnl_vector_fixed<double, 2> x2, y2;
    x2[0] = 1;
    x2[1] = 2;
    y2 = aff2.Transform(x2);
    std::cout << "Transform a vector:" << std::endl
              << y2 << std::endl;

    /* Back transform a vector */
    y2 = aff2.BackTransform(x2);
    std::cout << "Back transform a vector:" << std::endl
              << y2 << std::endl;

    /* Create a 3D transform and rotate in 3D */
    itk::AffineTransform<double,3> aff3;
    vnl_vector_fixed<double,3> axis;
    axis[0] = .707;
    axis[1] = .707;
    axis[2] = .707;
    aff3.Rotate3D(axis, 1.0, 1);
    std::cout << "Create and rotate a 3D transform:" << std::endl
              << aff3;

    /* Generate inverse transform */
    itk::AffineTransform<double,3> inv3;
    inv3 = aff3.Inverse();
    std::cout << "Create an inverse transformation:"
              << std::endl << inv3;

    return any;
}
