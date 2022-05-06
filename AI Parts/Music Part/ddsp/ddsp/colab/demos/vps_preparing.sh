
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

