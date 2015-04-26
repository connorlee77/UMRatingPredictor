//
//  svd.h
//  netflix_project
//
//  Created by Connor Lee on 4/25/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#ifndef __netflix_project__svd__
#define __netflix_project__svd__

#include <stdio.h>
#include "dataManager.h"
#include <assert.h>
#include <math.h>

extern const float GLOBAL_AVG_SET1;
extern const float GLOBAL_AVG_SET2;

extern const int TOTAL_USERS;
extern const int TOTAL_MOVIES;

extern double **user_feature_table;
extern double **movie_feature_table;


void initialize(int num_features);
void train();
double predictRating(int user, int movie, int num_features);
void trainFeatures(double learning_rate, int user, int movie, int rating, int num_feature);
void computeSVD(double learning_rate, int num_features, std::vector<testPoint *> train_data);



#endif /* defined(__netflix_project__svd__) */
