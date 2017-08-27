/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 * \brief Various functions for testing
 * 
 * 
 */
 
/**
 * Function to generate (fake) sensor data for testing. It needs a mean value and 
 * a margin of variation 
 * @param readings - the sensors array which needs data to be filled in
 * @param sizeReadings - the size of aforementioned readings array
 * @param meanValues - the mean value for fake sensor data
 * @param margins - the allowed variation around mean values
 */
void generateFakeSensorDataRandomNoise(double readings[], int sizeReadings, double meanValues[], double margins[]) {
    randomSeed();
    long randMin, randMax; 
    for(int i = 0; i < sizeReadings; i++) {
        long randMin = (long) ((meanValues[i] - margins[i]*meanValues[i])*1000.0);
        long randMax = (long) ((meanValues[i] + margins[i]*meanValues[i])*1000.0); 
        
        readings[i] = ((double) random(randMin, randMax))/1000.0; 
    }
}