//
//  svd.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/25/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "svd.h"
#include <limits.h>

const float GLOBAL_AVG_SET1 = 3.608609;
const float GLOBAL_AVG_SET2 = 3.608859;

const int TOTAL_USERS = 458293;
const int TOTAL_MOVIES = 17770;

double **user_feature_table = new double *[TOTAL_USERS];
double **movie_feature_table = new double *[TOTAL_MOVIES];


void initializeFeatureVectors(int num_features) {
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        
        user_feature_table[i] = new double[num_features];
        
        for(int k = 0; k < num_features; k++) {
            //user_feature_table[i][k] = 0.1;
            user_feature_table[i][k] = GLOBAL_AVG_SET2 / num_features;
        }
    }
    
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        
        movie_feature_table[i] = new double[num_features];
        
        for(int k = 0; k < num_features; k++) {
            //movie_feature_table[i][k] = 0.1;
            movie_feature_table[i][k] = GLOBAL_AVG_SET2 / num_features;
        }
    }
}


double predictRating(int user, int movie, int num_features) {
    
    double sum = 0.0;
    
    for(int i = 0; i < num_features; i++) {
        sum += (user_feature_table[user - 1][i] * movie_feature_table[movie - 1][i]);
    }
    
    assert(isfinite(sum));
    
    return sum;
}


/* Train feature #num_features */
void trainFeatures(double learning_rate, int user, int movie, int rating, int num_feature) {
    
    double error = (rating - predictRating(user, movie, num_feature + 1));
    
    double temp_user_feature = user_feature_table[user - 1][num_feature];
    user_feature_table[user - 1][num_feature] += learning_rate * error * movie_feature_table[movie - 1][num_feature];
    movie_feature_table[movie - 1][num_feature] += learning_rate * error * temp_user_feature;
    
    assert(user_feature_table[user - 1][num_feature] < 50 && user_feature_table[user - 1][num_feature] > -50);
    assert(movie_feature_table[movie - 1][num_feature] < 50 && movie_feature_table[movie - 1][num_feature] > -50);
}


void computeSVD(double learning_rate, int num_features, std::vector<testPoint *> train_data, int epochs) {
    
    initializeFeatureVectors(num_features);
    
    int user, movie, rating;
    double curr_rmse;
    
    int x = 0;
    while(x < epochs) {
        double sum = 0.0;
        for(int k = 0; k < train_data.size(); k++) {
            
            user = train_data[k] -> getUser();
            movie = train_data[k] -> getMovie();
            rating = train_data[k] -> getRating();
            
            for(int i = 0; i < num_features; i++) {
                trainFeatures(learning_rate, user, movie, rating, i);
            }
            sum += pow((rating - predictRating(user, movie, num_features)), 2);
        }
        
        curr_rmse = sqrt((sum / train_data.size()));
        x++;
        printf("Epoch %d, rsme: %f\n", x, curr_rmse);
    }

}
