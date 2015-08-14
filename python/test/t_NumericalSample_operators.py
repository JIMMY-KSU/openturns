#! /usr/bin/env python

from __future__ import print_function
import openturns as ot


# We create an empty ot.NumericalSample
sample1 = ot.NumericalSample(0, 2)
sample1.setName('Sample1')
sample1.setDescription(['a0', 'a1'])
sample1.add([10., 20.])
sample1.add([11., 21.])
sample1.add([12., 22.])
print('sample1=', repr(sample1))

# We create a new empty ot.NumericalSample
sample2 = ot.NumericalSample(0, 2)
sample2.setName('Sample2')
sample2.setDescription(['a0', 'a1'])
sample2.add([30., 40.])
sample2.add([31., 41.])
sample2.add([32., 42.])
print('sample2=', repr(sample2))

# Operator +|-
summation = ot.NumericalSample(sample1 + sample2)
substraction = ot.NumericalSample(sample2 - sample1)
print('sample1 + sample2=', repr(summation))
print('sample2 - sample1=', repr(substraction))

# Operator +=|-=
sample3 = ot.NumericalSample(sample2)
sample4 = ot.NumericalSample(sample2)
sample3 += sample1
sample4 -= sample1
print('sample3=', repr(sample3))
print('sample4=', repr(sample4))

sample5 = ot.NumericalSample(sample2)
m = ot.SquareMatrix([[1, 2], [3, 5]])
v = ot.NumericalPoint(2, 3.0)
t = ot.NumericalPoint(2, 5.0)

print('sample5 =', sample5)

print('sample*2:', sample5 * 2.)
print('sample/2:', sample5 / 2.)

print('sample*v:', sample5 * v)
print('sample/v:', sample5 / v)

print('sample*m:', sample5 * m)
print('sample/m:', sample5 / m)

# in-place
sample5 += t
print('sample+=t:', sample5)

sample5 -= t
print('sample-=t:', sample5)

sample5 *= 2.
print('sample*=2:', sample5)

sample5 /= 2.
print('sample/=2:', sample5)

sample5 *= v
print('sample*=v:', sample5)

sample5 /= v
print('sample/=v:', sample5)

sample5 *= m
print('sample*=m:', sample5)

sample5 /= m
print('sample/=m:', sample5)
