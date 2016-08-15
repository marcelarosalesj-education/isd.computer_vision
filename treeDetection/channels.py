import cv2
import numpy as np
import os

curr_dir = os.path.dirname(os.path.realpath(__file__))

img_arr = range(7)

#name = '/img_in/owens valley/owens_valley-band'
#name = '/img_in/bolivia/bolivia-band'
name = '/img_in/las vegas/vegas-band'

img_arr[0] = cv2.imread(curr_dir+name+'1.tif',0)
img_arr[1] = cv2.imread(curr_dir+name+'2.tif',0)
img_arr[2] = cv2.imread(curr_dir+name+'3.tif',0)
img_arr[3] = cv2.imread(curr_dir+name+'4.tif',0)
img_arr[4] = cv2.imread(curr_dir+name+'5.tif',0)
img_arr[5] = cv2.imread(curr_dir+name+'6.tif',0)
img_arr[6] = cv2.imread(curr_dir+name+'7.tif',0)

print img_arr[0].shape


cv2.imshow('image 4',img_arr[3])
cv2.imshow('image 5',img_arr[4])
cv2.imshow('image 1',img_arr[0])

img_451 = img_arr[0] + img_arr[4] + img_arr[3]
#img_451 = cv2.resize(img_451, (0,0), fx=0.5, fy=0.5) 
cv2.imshow('image 451',img_451)

#img_432 = img_arr[1] + img_arr[2] + img_arr[3]
#img_432 = cv2.resize(img_432, (0,0), fx=0.5, fy=0.5) 
#cv2.imshow('image 432',img_432)

cv2.waitKey(0)
cv2.destroyAllWindows()

