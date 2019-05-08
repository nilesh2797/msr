#!/bin/bash

# expects two arguments, e.g. ./run.sh Amazon ParabelOpt

dataset=$1
data_dir="Sandbox/Data/$dataset"
results_dir="Sandbox/Results/$dataset"
model_dir="Sandbox/Results/$dataset/model"

trn_ft_file="${data_dir}/trn_X_Xf.txt"
trn_lbl_file="${data_dir}/trn_X_Y.txt"
tst_ft_file="${data_dir}/tst_X_Xf.txt"
tst_lbl_file="${data_dir}/tst_X_Y.txt"
score_file="${results_dir}/score_mat.txt"

exe_prefix=$2
train_exe="${exe_prefix}/parabel_train"
test_exe="${exe_prefix}/parabel_predict"

# create the model folder
mkdir -p $model_dir

# training
# Reads training features (in $trn_ft_file), training labels (in $trn_lbl_file), and writes FastXML model to $model_dir
$train_exe $trn_ft_file $trn_lbl_file $model_dir -T 1 -s 0 -t 1 -b 1.0 -c 1.0 -m 100 -tcl 0.1 -tce 0 -e 0.0001 -n 20 -k 0 -q 0

# testing
# Reads test features (in $tst_ft_file), FastXML model (in $model_dir), and writes test label scores to $score_file
$test_exe $tst_ft_file $model_dir $score_file -t 1

# performance evaluation 
# matlab -nodesktop -nodisplay -r "cd('$PWD'); addpath(genpath('../Tools')); trn_X_Y = read_text_mat('$trn_lbl_file'); tst_X_Y = read_text_mat('$tst_lbl_file'); wts = inv_propensity(trn_X_Y,0.55,1.5); score_mat = read_text_mat('$score_file'); get_all_metrics(score_mat, tst_X_Y, wts); exit;"