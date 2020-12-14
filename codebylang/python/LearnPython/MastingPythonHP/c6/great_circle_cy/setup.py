#!-*-coding:utf8-*-
from distutils.core import setup
from Cython.Build import cythonize


#python setup.py build 可以生成直接可以导入的.so文件 
setup(
        name='great_circle app',
        ext_modules=cythonize('great_circle_cy.pyx'),
        )
