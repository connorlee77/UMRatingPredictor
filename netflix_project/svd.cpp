//
//  svd.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/25/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "svd.h"

const float GLOBAL_AVG_SET1 = 3.608609;
const float GLOBAL_AVG_SET2 = 3.608859;

const int TOTAL_USERS = 458293;
const int TOTAL_MOVIES = 17770;
const int TOTAL_DAYS = 2243;

//const float REG_A = 0.0255;
//const float LEARNING_A = 0.00267;
//
//const float REG_B = 3.95;
//const float LEARNING_B = 0.00000311;
//
//const float REG_C = 0.00231;
//const float LEARNING_C = 0.00257;
//
//const float REG_D = 0.0255;
//const float LEARNING_D = 0.000488;
//
//const float REG_E = 0.0929;
//const float LEARNING_E = 0.000115;
//
//const float REG_F = 0.0476;
//const float LEARNING_F = 0.00564;
//
//const float REG_G = 0.0190;
//const float LEARNING_G = 0.00103;
//
//const float REG_H = 0.000000011;
//const float LEARNING_H = 0.00236;

const float REG_A = 0.0255;
const float LEARNING_A = 0.00267;

const float REG_B = 3.95;
const float LEARNING_B = 0.00000311;

const float REG_C = 0.00231;
const float LEARNING_C = 0.00257;

const float REG_D = 0.0255;
const float LEARNING_D = 0.000488;

const float REG_E = 0.0929;
const float LEARNING_E = 0.000115;

const float REG_F = 0.0476;
const float LEARNING_F = 0.00564;

const float REG_G = 0.0190;
const float LEARNING_G = 0.00103;

const float REG_H = 0.000000011;
const float LEARNING_H = 0.00236;

const float BETA = 0.4;
const float LOG_BASE = 6.76;
const int highVal = 2651;

float LRATE;
float REG = 0.02;
int NUMFEATURES;

float **user_feature_table;
float *user_rating_deviation_table;
float *user_mean_rating_date_table;
float *user_time_deviation_scaling_table;
float **user_time_dependent_deviation_table;
float *user_constant_time_dependent_baseline_scaling_table;
float **user_varying_time_dependent_baseline_scaling_table;
int **user_frequency_table;

float **movie_feature_table;
float *movie_rating_deviation_table;
float **movie_time_changing_bias_table;
float **movie_frequency_bias_table;

int *dataArray;

float CURR_USER_RATING_DEVIATION;
float CURR_USER_TIME_DEVIATION;
float CURR_USER_TIME_DEVIATION_SCALING_FACTOR;
float CURR_USER_TIME_DEPENDENT_DEVIATION;
float CURR_USER_CONSTANT_TIME_DEPENDENT_BASELINE_SCALING_FACTOR;
float CURR_USER_VARYING_TIME_DEPENDENT_BASELINE_SCALING_FACTOR;

float CURR_MOVIE_RATING_DEVIATION;
int CURR_MOVIE_TIME_BIN;
float CURR_MOVIE_TIME_CHANGING_BIAS;
int CURR_ADJUSTED_FREQUENCY;
float CURR_MOVIE_FREQUENCY_BIAS;

bool printVectorInitInfo = 0;
bool printPredictionInfo = 0;
bool printTrainRMSE = 1;

float getRandom() {
    //return 10.0 / 10.0 * ((double) rand() / ((double) RAND_MAX)) - 0.0;
    int num = ((int) rand()) % 100;
    return 2.0 * num / 10000.0 - 0.01;
}

void initializeFeatureVectors() {
    srand (static_cast <unsigned> (time(0)));
    
    /*
     * Initialize user_feature_table
     */
    user_feature_table = new float *[TOTAL_USERS];
    printf("userFeatures");
    
    float constant = sqrt(((float) GLOBAL_AVG_SET1) / NUMFEATURES);
    float randomAcc;
    for(int i = 0; i < TOTAL_USERS; i++) {
        user_feature_table[i] = new float[NUMFEATURES];
        
        for(int j = 0; j < NUMFEATURES; j++) {
            randomAcc = getRandom();
            user_feature_table[i][j] = constant + randomAcc;
        }
        
    }
    printf("\n");

    /*
     * End initialization of user_feature_table
     */
    

//    /*
//     * Initialize user_rating_deviation_table
//     */
//    user_rating_deviation_table = new float[TOTAL_USERS];
//    
//    ifstream userRatingDeviationStream;
//    userRatingDeviationStream.open(userRatingDeviationFile, ios::in|ios::binary);
//    if(!userRatingDeviationStream.is_open()) {
//        fprintf(stderr, "user rating deviation binary file was not opened!\n");
//        exit(0);
//    }
//    userRatingDeviationStream.seekg (0, ios::beg);
//    
//    userRatingDeviationStream.read(reinterpret_cast<char*> (user_rating_deviation_table), sizeof(float) * TOTAL_USERS);
//    
//    userRatingDeviationStream.close();
//    /*
//     * End initialization of user_rating_deviation_table
//     */
//    
//    
//    /*
//     * Initialize user_mean_rating_date_table
//     */
//    user_mean_rating_date_table = new float[TOTAL_USERS];
//    ifstream userMeanRatingDateStream;
//    userMeanRatingDateStream.open(userMeanTimeRatingFile, ios::in|ios::binary);
//    if(!userMeanRatingDateStream.is_open()) {
//        fprintf(stderr, "user mean rating rate binary file was not opened!\n");
//        exit(0);
//    }
//    userMeanRatingDateStream.seekg (0, ios::beg);
//    
//    userMeanRatingDateStream.read(reinterpret_cast<char*> (user_mean_rating_date_table), sizeof(float) * TOTAL_USERS);
//    
//    userMeanRatingDateStream.close();
//    /*
//     * End initialization of user_mean_rating_date_table
//     */
//    
//    /*
//     * Initialize user_time_deviation_scaling_table
//     */
//    user_time_deviation_scaling_table = new float[TOTAL_USERS];
//    /*
//     * End initialization of user_time_deviation_scaling_table
//     */
//    
//    /*
//     * Initialize user_time_dependent_deviation_table
//     */
//    user_time_dependent_deviation_table = new float*[TOTAL_USERS];
//    for (int i = 0; i < TOTAL_USERS; i++) {
//        user_time_dependent_deviation_table[i] = new float[TOTAL_DAYS];
//    }
//    /*
//     * End initialization of user_time_dependent_deviation_table
//     */
//    
//    /*
//     * Initialize user_constant_time_dependent_baseline_scaling_table
//     */
//    user_constant_time_dependent_baseline_scaling_table = new float[TOTAL_USERS];
//    std::fill(user_constant_time_dependent_baseline_scaling_table, user_constant_time_dependent_baseline_scaling_table + TOTAL_USERS, 1.0f);
//    /*
//     * End initialization of user_constant_time_dependent_baseline_scaling_table
//     */
//    
//    /*
//     * Initialize user_varying_time_dependent_baseline_scaling_table
//     */
//    user_varying_time_dependent_baseline_scaling_table = new float*[TOTAL_USERS];
//    for (int i = 0; i < TOTAL_USERS; i++) {
//        user_varying_time_dependent_baseline_scaling_table[i] = new float[TOTAL_DAYS];
//    }
//    /*
//     * End initialization of user_varying_time_dependent_baseline_scaling_table
//     */
//    
//    /*
//     * Initialize user_frequency_table
//     */
//    user_frequency_table = new int*[TOTAL_USERS];
//    
//    ifstream userFrequencyStream;
//    userFrequencyStream.open(userFrequenciesFile, ios::in|ios::binary);
//    if(!userFrequencyStream.is_open()) {
//        fprintf(stderr, "user frequency binary file was not opened!\n");
//        exit(0);
//    }
//    userFrequencyStream.seekg(0, ios::beg);
//    
//    for(int i = 0; i < TOTAL_USERS; i++){
//        user_frequency_table[i] = new int[TOTAL_DAYS];
//        userFrequencyStream.read(reinterpret_cast<char*> (user_frequency_table[i]), sizeof(int) * TOTAL_DAYS);
//    }
//    userFrequencyStream.close();
//    /*
//     * End initialization of user_frequency_table
//     */
//    
//    /*
//     * Print sample user values, if wanted
//     */
//    int randUser = rand() % TOTAL_USERS;
//    int randDay = rand() % TOTAL_DAYS;
//    if(printVectorInitInfo){
//        printf("Sample user features, first: %f, last: %f\n", user_feature_table[randUser][0], user_feature_table[randUser][NUMFEATURES - 1]);
//        printf("Sample user rating deviation: %f\n", user_rating_deviation_table[randUser]);
//        printf("Sample user mean rating date: %f\n", user_mean_rating_date_table[randUser]);
//        printf("Sample user time deviation scaling factor: %f\n", user_time_deviation_scaling_table[randUser]);
//        printf("Sample user time dependent deviation, first: %f, day %d: %f, last: %f\n", user_time_dependent_deviation_table[TOTAL_USERS - 1][0], randDay + 1, user_time_dependent_deviation_table[TOTAL_USERS - 1][randDay], user_time_dependent_deviation_table[randUser][TOTAL_DAYS - 1]);
//        printf("Sample user constant time dependent baseline scaling factor: %f\n", user_constant_time_dependent_baseline_scaling_table[randUser]);
//        printf("Sample user varying time dependent baseline scaling factors, first: %f, day %d: %f, last: %f\n", user_varying_time_dependent_baseline_scaling_table[randUser][0], randDay + 1, user_varying_time_dependent_baseline_scaling_table[randUser][randDay],user_varying_time_dependent_baseline_scaling_table[randUser][TOTAL_DAYS - 1]);
//        printf("user frequencies for user %d: ", randUser);
//        for(int i = 0; i < TOTAL_DAYS; i++){
//            printf("%d ", user_frequency_table[randUser][i]);
//        }
//        printf("\n");
//    }

    
    /*
     * Initialize movie_feature_table
     */
    printf("movieFeatures");
    movie_feature_table = new float *[TOTAL_MOVIES];
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        movie_feature_table[i] = new float[NUMFEATURES];
        
        for(int j = 0; j < NUMFEATURES; j++) {
            randomAcc = getRandom();
            movie_feature_table[i][j] = constant + randomAcc;
        }
    }
    printf("\n");
    /*
     * End initialization of movie_feature_table
     */
    
    
//    /*
//     * Initialize movie_rating_deviation_table
//     */
//    movie_rating_deviation_table = new float[TOTAL_MOVIES];
//    
//    ifstream movieRatingDeviationStream;
//    movieRatingDeviationStream.open(movieRatingDeviationFile, ios::in|ios::binary);
//    if(!movieRatingDeviationStream.is_open()) {
//        fprintf(stderr, "binary file was not opened!\n");
//        exit(0);
//    }
//    movieRatingDeviationStream.seekg (0, ios::beg);
//    
//    movieRatingDeviationStream.read(reinterpret_cast<char*> (movie_rating_deviation_table), sizeof(float) * TOTAL_MOVIES);
//    
//    movieRatingDeviationStream.close();
//    /*
//     * End initialization of movie_rating_deviation_table
//     */
//    
//    /*
//     * Initialize movie_time_changing_bias_table
//     */
//    movie_time_changing_bias_table = new float*[TOTAL_MOVIES];
//    for(int i = 0; i < TOTAL_MOVIES; i++) {
//        movie_time_changing_bias_table[i] = new float[30];
//    }
//    /*
//     * End initialization of movie_time_changing_bias_table
//     */
//    
//    /*
//     * Initialize movie_frequency_bias_table
//     */
//    
//    int highestAdjustedVal = (float) log(highVal)/ (float) log(LOG_BASE) + 1;
//    
//    movie_frequency_bias_table = new float*[TOTAL_MOVIES];
//    for (int i = 0; i < TOTAL_MOVIES; i++) {
//        movie_frequency_bias_table[i] = new float[highestAdjustedVal];
//    }
//    /*
//     * End initialization of movie_frequency_bias_table
//     */
//    
//    /*
//     * Print sample movie values, if wanted
//     */
//    if(printVectorInitInfo){
//        printf("Sample movie features, first: %f, last: %f\n", movie_feature_table[TOTAL_MOVIES - 1][0], movie_feature_table[TOTAL_MOVIES - 1][NUMFEATURES - 1]);
//        printf("Sample movie rating deviation: %f\n", movie_rating_deviation_table[TOTAL_MOVIES - 1]);
//        printf("Sample movie time changing bias, first: %f, last: %f\n", movie_time_changing_bias_table[TOTAL_MOVIES - 1][0], movie_time_changing_bias_table[TOTAL_MOVIES - 1][29]);
//        printf("Highest adjust value: %d\n", highestAdjustedVal);
//        printf("Sample movie frequency biases, first: %f, last: %f\n", movie_frequency_bias_table[TOTAL_MOVIES - 1][0], movie_frequency_bias_table[TOTAL_MOVIES - 1][highestAdjustedVal - 1]);
//    }
}


float predictRating(int user, int movie, int date) {
    float sum = 0.0, timeDeviation;
    int sign = 1;
    
    /*
     * Include prediction using user and movie features
     */
    for(int i = 0; i < NUMFEATURES; i++) {
        sum += (user_feature_table[user - 1][i] * movie_feature_table[movie - 1][i]);
    }

    
//    CURR_USER_RATING_DEVIATION = user_rating_deviation_table[user - 1];
//    timeDeviation = date - user_mean_rating_date_table[user - 1];
//    if(timeDeviation < 0)
//        sign = -1;
//    CURR_USER_TIME_DEVIATION = sign * pow(abs(timeDeviation), BETA);
//    CURR_USER_TIME_DEVIATION_SCALING_FACTOR = user_time_deviation_scaling_table[user - 1];
//    CURR_USER_TIME_DEPENDENT_DEVIATION = user_time_dependent_deviation_table[user - 1][date - 1];
//    CURR_USER_CONSTANT_TIME_DEPENDENT_BASELINE_SCALING_FACTOR = user_constant_time_dependent_baseline_scaling_table[user - 1];
//    CURR_USER_VARYING_TIME_DEPENDENT_BASELINE_SCALING_FACTOR = user_varying_time_dependent_baseline_scaling_table[user - 1][date - 1];
//    
//    CURR_MOVIE_RATING_DEVIATION = movie_rating_deviation_table[movie - 1];
//    CURR_MOVIE_TIME_BIN = ((float) date/ (float) TOTAL_DAYS) * 30;
//    CURR_MOVIE_TIME_CHANGING_BIAS = movie_time_changing_bias_table[movie - 1][CURR_MOVIE_TIME_BIN];
//    CURR_ADJUSTED_FREQUENCY = (float) log(user_frequency_table[user - 1][date - 1])/ (float) log(LOG_BASE);
//    CURR_MOVIE_FREQUENCY_BIAS = movie_frequency_bias_table[movie - 1][CURR_ADJUSTED_FREQUENCY];

    //debugging
//    printf("User rating deviation: %f\n", CURR_USER_RATING_DEVIATION);
//    printf("User non-adjusted time deviation: %f\n", timeDeviation);
//    printf("User adjusted time deviation: %f\n", CURR_USER_TIME_DEVIATION);
//    printf("User time deviation scaling factor: %f\n", CURR_USER_TIME_DEVIATION_SCALING_FACTOR);
//    printf("User time dependent deviation: %f\n", CURR_USER_TIME_DEPENDENT_DEVIATION);
//    printf("User constant time dependent baseline scaling factor: %f\n", CURR_USER_CONSTANT_TIME_DEPENDENT_BASELINE_SCALING_FACTOR);
//    printf("User varying time dependent baseline scaling factor: %f\n", CURR_USER_VARYING_TIME_DEPENDENT_BASELINE_SCALING_FACTOR);
//    
//    printf("Movie rating deviation: %f\n", CURR_MOVIE_RATING_DEVIATION);
//    printf("Movie time bin: %d\n", CURR_MOVIE_TIME_BIN);
//    printf("Movie time changing bias: %f\n", CURR_MOVIE_TIME_CHANGING_BIAS);
//    printf("Adjusted frequency: %d\n", CURR_ADJUSTED_FREQUENCY);
//    printf("Movie frequency bias: %f\n", CURR_MOVIE_FREQUENCY_BIAS);
    
    
    
    /*
     * Include all baseline predictors
     */
//    sum += GLOBAL_AVG_SET1 + CURR_USER_RATING_DEVIATION + CURR_USER_TIME_DEVIATION_SCALING_FACTOR * CURR_USER_TIME_DEVIATION + CURR_USER_TIME_DEPENDENT_DEVIATION + (CURR_MOVIE_RATING_DEVIATION + CURR_MOVIE_TIME_CHANGING_BIAS) * (CURR_USER_CONSTANT_TIME_DEPENDENT_BASELINE_SCALING_FACTOR + CURR_USER_VARYING_TIME_DEPENDENT_BASELINE_SCALING_FACTOR) + CURR_MOVIE_FREQUENCY_BIAS;
    
    /*
     * Print prediction information if wanted
     */
    if(printPredictionInfo){
        printf("User, movie, date: %d %d %d\n", user, movie, date);
        
        printf("User rating deviation: %f\n", CURR_USER_RATING_DEVIATION);
        printf("User non-adjusted time deviation: %f\n", timeDeviation);
        printf("User adjusted time deviation: %f\n", CURR_USER_TIME_DEVIATION);
        printf("User time deviation scaling factor: %f\n", CURR_USER_TIME_DEVIATION_SCALING_FACTOR);
        printf("User time dependent deviation: %f\n", CURR_USER_TIME_DEPENDENT_DEVIATION);
        printf("User constant time dependent baseline scaling factor: %f\n", CURR_USER_CONSTANT_TIME_DEPENDENT_BASELINE_SCALING_FACTOR);
        printf("User varying time dependent baseline scaling factor: %f\n", CURR_USER_VARYING_TIME_DEPENDENT_BASELINE_SCALING_FACTOR);
        
        printf("Movie rating deviation: %f\n", CURR_MOVIE_RATING_DEVIATION);
        printf("Movie time bin: %d\n", CURR_MOVIE_TIME_BIN);
        printf("Movie time changing bias: %f\n", CURR_MOVIE_TIME_CHANGING_BIAS);
        printf("Adjusted frequency: %d\n", CURR_ADJUSTED_FREQUENCY);
        printf("Movie frequency bias: %f\n", CURR_MOVIE_FREQUENCY_BIAS);
        
        printf("Rating prediction: %f\n\n", sum);
    }
    return sum;
}


void computeSVD(float learning_rate, int num_features, int epochs, int* train_data, int* probe_data) {
    LRATE = learning_rate;
    NUMFEATURES = num_features;
    dataArray = train_data;

    float start, end;
    float duration;
    
    start = clock();
    initializeFeatureVectors();
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    
    printf("Feature initialization took %f seconds\n", duration);
    
    float sum, error, userVal, movieVal, adjustUser, adjustMovie, oldTrainRMSE = 3.0f, newTrainRMSE, oldProbeRMSE = 3.0f, newProbeRMSE;
    int user, movie, rating, date, randUser, randFeature, randMovie;
    
    for(int k = 0; k < epochs; k++) {
        start = clock();
        printf("Training epoch %d\n", k + 1);

        for(int j = 0; j < BASE_SIZE; j++) {
            user = dataArray[4 * j];
            movie = dataArray[4 * j + 1];
            date = dataArray[4 * j + 2];
            rating = dataArray[4 * j + 3];
            
            //debugging
            float predicted = predictRating(user, movie, date);
            
            error = rating - predicted;
            
            //debugging
//            printf("rating: %d\n", rating);
//            printf("predictedRating: %f\n", predicted);
//            printf("error: %f\n\n", error);
            
            assert(error > -10 && error < 10);
            
            //Train user and movie features
            for(int i = 0; i < NUMFEATURES; i++){
                userVal = user_feature_table[user - 1][i];
                movieVal = movie_feature_table[movie - 1][i];

                user_feature_table[user - 1][i] += LRATE * (error * movieVal - REG * userVal);
                movie_feature_table[movie - 1][i] += LRATE * (error * userVal - REG * movieVal);
            }
            
//            //Train user rating deviation
//            user_rating_deviation_table[user - 1] += LEARNING_A * (error - REG_A * CURR_USER_RATING_DEVIATION);
//            
//            //Train user time deviation scaling factor
//            user_time_deviation_scaling_table[user - 1] += LEARNING_B * (CURR_USER_TIME_DEVIATION * error - REG_B * CURR_USER_TIME_DEVIATION_SCALING_FACTOR);
//            
//            //Train user time dependent deviation
//            user_time_dependent_deviation_table[user - 1][date - 1] += LEARNING_C * (error - REG_C * CURR_USER_TIME_DEPENDENT_DEVIATION);
//            
//            //Train user constant time dependent baseline scaling factor
//            user_constant_time_dependent_baseline_scaling_table[user - 1] += LEARNING_F * ((CURR_MOVIE_RATING_DEVIATION + CURR_MOVIE_TIME_CHANGING_BIAS) * error - REG_F * (CURR_USER_CONSTANT_TIME_DEPENDENT_BASELINE_SCALING_FACTOR - 1.0f));
//            
//            //Train user varying time dependent baseline scaling factor
//            user_varying_time_dependent_baseline_scaling_table[user - 1][date - 1] += LEARNING_G * ((CURR_MOVIE_RATING_DEVIATION + CURR_MOVIE_TIME_CHANGING_BIAS) * error - REG_G * CURR_USER_VARYING_TIME_DEPENDENT_BASELINE_SCALING_FACTOR);
//            
//            //Train movie rating deviation
//            movie_rating_deviation_table[movie - 1] += LEARNING_D * ((CURR_USER_CONSTANT_TIME_DEPENDENT_BASELINE_SCALING_FACTOR + CURR_USER_VARYING_TIME_DEPENDENT_BASELINE_SCALING_FACTOR) * error - REG_D * CURR_MOVIE_RATING_DEVIATION);
//            
//            //Train movie time changing bias
//            movie_time_changing_bias_table[movie - 1][CURR_MOVIE_TIME_BIN] += LEARNING_E * ((CURR_USER_CONSTANT_TIME_DEPENDENT_BASELINE_SCALING_FACTOR + CURR_USER_VARYING_TIME_DEPENDENT_BASELINE_SCALING_FACTOR) * error - REG_E * CURR_MOVIE_TIME_CHANGING_BIAS);
//            
//            //Train movie frequency bias
//            movie_frequency_bias_table[movie - 1][CURR_ADJUSTED_FREQUENCY] += LEARNING_H * (error - REG_H * CURR_MOVIE_FREQUENCY_BIAS);
//            
        }


        for(int i = 0; i < 10000; i++){
            randUser = rand() % TOTAL_USERS;
            randMovie = rand() % TOTAL_MOVIES;
            randFeature = rand() % NUMFEATURES;
            
            adjustUser = user_feature_table[randUser][randFeature];
            assert(adjustUser < 50 && adjustUser > -50);
            
            adjustMovie = movie_feature_table[randMovie][randFeature];
            assert(adjustMovie < 50 && adjustMovie > -50);
        }
        end = clock();
        duration=(end-start)/CLOCKS_PER_SEC;
        
        printf("Epoch %d took %f seconds\n",k + 1, duration);
        
        if(printTrainRMSE){
            sum = 0.0;
            for (int j = 0; j < BASE_SIZE; j++) {
                user = dataArray[4 * j];
                movie = dataArray[4 * j + 1];
                date = dataArray[4 * j + 2];
                rating = dataArray[4 * j + 3];
                sum += powf(rating - predictRating(user, movie, date), 2);
            }
        
            newTrainRMSE = powf(sum/(BASE_SIZE), 0.5);
            
            printf("Training RMSE, old: %f, new %f\n", oldTrainRMSE, newTrainRMSE);
            if(newTrainRMSE - oldTrainRMSE > 0){
                fprintf(stderr, "Training set RMSE went up, exiting.\n");
                exit(0);
            }
            
            oldTrainRMSE = newTrainRMSE;
        }
        
        sum = 0.0;
        
        for (int j = 0; j < PROBE_SIZE; j++) {
            user = probe_data[4 * j];
            movie = probe_data[4 * j + 1];
            date = probe_data[4 * j + 2];
            rating = probe_data[4 * j + 3];
            sum += powf(rating - predictRating(user, movie, date), 2);
        }
        
        newProbeRMSE = powf(sum/(PROBE_SIZE), 0.5);
        
        printf("Probe RMSE, old: %f, new %f\n", oldProbeRMSE, newProbeRMSE);
        

        if(oldProbeRMSE - newProbeRMSE < 0.00001){
            fprintf(stderr, "Probe RMSE drop is miniscule. Training done.\n");
            break;
        }
        
        oldProbeRMSE = newProbeRMSE;
//        if(k > 40 && k % 5 == 0)
//            LRATE = 0.9 * LRATE;
    }

}
