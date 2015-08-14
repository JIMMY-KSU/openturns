#! /usr/bin/env python

from __future__ import print_function
from openturns import *

TESTPREAMBLE()
RandomGenerator.SetSeed(0)

try:
    # Instanciate one distribution object
    distribution = Gumbel(2.0, -0.5)
    print("Distribution ", repr(distribution))
    print("Distribution ", distribution)

    # Is this distribution elliptical ?
    print("Elliptical = ", distribution.isElliptical())

    # Is this distribution continuous ?
    print("Continuous = ", distribution.isContinuous())

    # Test for realization of distribution
    oneRealization = distribution.getRealization()
    print("oneRealization=", repr(oneRealization))

    # Test for sampling
    size = 10000
    oneSample = distribution.getSample(size)
    print("oneSample first=", repr(oneSample[0]), " last=", repr(oneSample[1]))
    print("mean=", repr(oneSample.computeMean()))
    print("covariance=", repr(oneSample.computeCovariance()))

    # Define a point
    point = NumericalPoint(distribution.getDimension(), 1.0)
    print("Point= ", repr(point))

    # Show PDF and CDF at point
    eps = 1e-5
    # derivative of PDF with regards its arguments
    DDF = distribution.computeDDF(point)
    print("ddf     =", repr(DDF))
    # by the finite difference technique
    print("ddf (FD)=", repr(NumericalPoint(1, (distribution.computePDF(
        point + NumericalPoint(1, eps)) - distribution.computePDF(point + NumericalPoint(1, -eps))) / (2.0 * eps))))

    # PDF value
    LPDF = distribution.computeLogPDF(point)
    print("log pdf=%.6f" % LPDF)
    PDF = distribution.computePDF(point)
    print("pdf     =%.6f" % PDF)
    # by the finite difference technique from CDF
    print("pdf (FD)=%.6f" % ((distribution.computeCDF(point + NumericalPoint(1, eps)) -
                              distribution.computeCDF(point + NumericalPoint(1, -eps))) / (2.0 * eps)))

    # derivative of the PDF with regards the parameters of the distribution
    CDF = distribution.computeCDF(point)
    print("cdf=%.6f" % CDF)
    CCDF = distribution.computeComplementaryCDF(point)
    print("ccdf=%.6f" % CCDF)
    PDFgr = distribution.computePDFGradient(point)
    print("pdf gradient     =", repr(PDFgr))
    # by the finite difference technique
    PDFgrFD = NumericalPoint(2)
    PDFgrFD[0] = (Gumbel(distribution.getAlpha() + eps, distribution.getBeta()).computePDF(point)
                  - Gumbel(distribution.getAlpha() - eps, distribution.getBeta()).computePDF(point)) / (2.0 * eps)
    PDFgrFD[1] = (Gumbel(distribution.getAlpha(), distribution.getBeta() + eps).computePDF(point)
                  - Gumbel(distribution.getAlpha(), distribution.getBeta() - eps).computePDF(point)) / (2.0 * eps)
    print("pdf gradient (FD)=", repr(PDFgrFD))

    # derivative of the PDF with regards the parameters of the distribution
    CDFgr = distribution.computeCDFGradient(point)
    print("cdf gradient     =", repr(CDFgr))
    # by the finite difference technique
    CDFgrFD = NumericalPoint(2)
    CDFgrFD[0] = (Gumbel(distribution.getAlpha() + eps, distribution.getBeta()).computeCDF(point)
                  - Gumbel(distribution.getAlpha() - eps, distribution.getBeta()).computeCDF(point)) / (2.0 * eps)
    CDFgrFD[1] = (Gumbel(distribution.getAlpha(), distribution.getBeta() + eps).computeCDF(point)
                  - Gumbel(distribution.getAlpha(), distribution.getBeta() - eps).computeCDF(point)) / (2.0 * eps)
    print("cdf gradient (FD)=", repr(CDFgrFD))

    # quantile
    quantile = distribution.computeQuantile(0.95)
    print("quantile=", repr(quantile))
    print("cdf(quantile)=%.6f" % distribution.computeCDF(quantile))
    mean = distribution.getMean()
    print("mean=", repr(mean))
    standardDeviation = distribution.getStandardDeviation()
    print("standard deviation=", repr(standardDeviation))
    skewness = distribution.getSkewness()
    print("skewness=", repr(skewness))
    kurtosis = distribution.getKurtosis()
    print("kurtosis=", repr(kurtosis))
    covariance = distribution.getCovariance()
    print("covariance=", repr(covariance))
    parameters = distribution.getParametersCollection()
    print("parameters=", repr(parameters))
    for i in range(6):
        print("standard moment n=", i, " value=",
              distribution.getStandardMoment(i))
    print("Standard representative=", distribution.getStandardRepresentative())

    # Specific to this distribution
    mu = distribution.getMu()
    print("mu=%.6f" % mu)
    sigma = distribution.getSigma()
    print("sigma=%.6f" % sigma)
    newDistribution = Gumbel(mu, sigma, Gumbel.MUSIGMA)
    print("alpha from (mu, sigma)=%.6f" % newDistribution.getAlpha())
    print("beta from (mu, sigma)=%.6f" % newDistribution.getBeta())

    a = distribution.getA()
    print("a=%.6f" % a)
    b = distribution.getB()
    print("b=%.6f" % b)
    newDistribution = Gumbel(a, b, Gumbel.AB)
    print("alpha from (a, b)=%.6f" % newDistribution.getAlpha())
    print("beta from (a, b)=%.6f" % newDistribution.getBeta())

except:
    import sys
    print("t_Gumbel.py", sys.exc_info()[0], sys.exc_info()[1])
