
apk update
apk upgrade
apk add git

apk add --update python3 py3-pip

%%capture
#@title Install dependencies
#@markdown 
rm -rf neural-waveshaping-synthesis
git clone https://github.com/ben-hayes/neural-waveshaping-synthesis.git
%cd neural-waveshaping-synthesis
pip install youtube-dl pytorch-lightning auraloss==0.2.1 librosa==0.8.0 torchcrepe==0.0.12 wandb
pip install -q https://github.com/tugstugi/dl-colab-notebooks/archive/colab_utils.zip
pip install -e .
cat <<EOF > import.py

#!/bin/bash
%%capture
#@title Make imports

import os
import time
import warnings
warnings.filterwarnings("ignore")

from dl_colab_notebooks.audio import record_audio
import gin
from google.colab import files
import IPython.display as ipd
import matplotlib.pyplot as plt
import numpy as np
from scipy.io import wavfile
import torch

from neural_waveshaping_synthesis.data.utils.loudness_extraction import extract_perceptual_loudness
from neural_waveshaping_synthesis.data.utils.mfcc_extraction import extract_mfcc
from neural_waveshaping_synthesis.data.utils.f0_extraction import extract_f0_with_crepe
from neural_waveshaping_synthesis.data.utils.preprocess_audio import preprocess_audio, convert_to_float32_audio, make_monophonic, resample_audio
from neural_waveshaping_synthesis.models.modules.shaping import FastNEWT
from neural_waveshaping_synthesis.models.neural_waveshaping import NeuralWaveshaping

try:
  gin.constant("device", "cuda" if torch.cuda.is_available() else "cpu")
except ValueError as err:
  pass
gin.parse_config_file("gin/models/newt.gin")
gin.parse_config_file("gin/data/urmp_4second_crepe.gin")

checkpoints = dict(Violin="vn", Flute="fl", Trumpet="tpt")

EOF

