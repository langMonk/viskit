# Mammoth Dataset Analysis

## Setup
1. download .bin and .csv files from [here](https://drive.google.com/drive/folders/1VBnYCLVMOn_p1wlFvr_umuId9gpMaZab?usp=sharing) and put them inside /data/ folder (.bin files are required for IVHD, you can generate .csv files yourself however then you will also need to generate .bin files too)
2. install jupyter notebook + packages in requirements.txt
3. you should be ready to go

## What's inside
there is a single jupyter notebook including:
* analysis of Mammoth dataset using t-SNE, UMAP, TriMAP, PaCMAP and IVHD
* comparison of methods above using additional 2 generated datasets:
    * 30d ball with 2 classes divided by plane d[0] = 0
    * 30d ball inside sphere inside sphere

_Made for project for Visualization of Big Data by Karol Koptyra, Jakub Skulski_