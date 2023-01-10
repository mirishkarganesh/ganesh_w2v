# ganesh_w2v

Step0
```
sudo apt-get install liblzma-dev libbz2-dev libzstd-dev libsndfile1-dev libopenblas-dev libfftw3-dev libgflags-dev libgoogle-glog-dev
sudo apt install build-essential cmake libboost-system-dev libboost-thread-dev libboost-program-options-dev libboost-test-dev libeigen3-dev zlib1g-dev libbz2-dev liblzma-dev

pip install joblib==1.0.0 tqdm==4.56.0 numpy==1.20.0 pandas==1.2.2 progressbar2==3.53.1 python_Levenshtein==0.12.2 editdistance==0.3.1 omegaconf==2.0.6 tensorboard==2.4.1 tensorboardX==2.1 wandb jiwer sox cmake packaging soundfile swifter indic-nlp-library 
```

Step1
```
git clone https://github.com/mirishkarganesh/ganesh_w2v.git
cd ganesh_w2v
cd fairseq
pip install -e .
cd ..
```
Step2
```
cd kenlm
mkdir -p build && cd build
cmake .. 
make -j 16
cd ..
export KENLM_ROOT=$PWD
cd ..
```
Step3
```
cd flashlight/bindings/python
export USE_MKL=0
export USE_CUDA=0
python setup.py install
```
Only for Inference follow Step4
```
pip uninstall torch==1.12.0 protobuf==4.21.12
pip install torch==1.10.0 fastapi pydub uvicorn python-multipart webrtcvad 
```
