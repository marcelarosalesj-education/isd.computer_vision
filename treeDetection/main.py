"""
You must have clarifai installed:
pip install git+git://github.com/Clarifai/clarifai-python.git

Do this before running:
export CLARIFAI_APP_ID=<an_application_id_from_your_account>
export CLARIFAI_APP_SECRET=<an_application_secret_from_your_account>

"""

from clarifai.client import ClarifaiApi
clarifai_api = ClarifaiApi() # assumes environment variables are set.
result = clarifai_api.tag_images(open('/home/marcela/Repos/vision/treeDetection/img_in/tree2.png', 'rb'))

print result

#import pdb; pdb.set_trace()