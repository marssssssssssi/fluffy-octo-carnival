#include <vector>
#include <algorithm>

using std::vector;
using std::reverse;

double calculatePathLength(const vector<int>& tour, const vector<vector<int>>& distanceMatrix) {
    double length = 0.0;
    int stops = tour.size();
    
    for (int idx = 0; idx < stops - 1; idx++) {
        int current = tour[idx];
        int next = tour[idx + 1];
        length += distanceMatrix[current][next];
    }
    return length;
}

vector<int> optimizeRoute(vector<int> initialRoute, const vector<vector<int>>& distanceMatrix) {
    bool foundImprovement;
    int routeSize = initialRoute.size();
    
    do {
        foundImprovement = false;
        
        for (int first = 1; first < routeSize - 2; first++) {
            for (int second = first + 1; second < routeSize - 1; second++) {
                // Текущие соединения
                int prevFirst = initialRoute[first - 1];
                int currentFirst = initialRoute[first];
                int currentSecond = initialRoute[second];
                int nextSecond = initialRoute[second + 1];
                
                // Сравниваем текущую и потенциальную длину
                double currentLength = distanceMatrix[prevFirst][currentFirst] + 
                                     distanceMatrix[currentSecond][nextSecond];
                double potentialLength = distanceMatrix[prevFirst][currentSecond] + 
                                       distanceMatrix[currentFirst][nextSecond];
                
                // Если нашли улучшение - перестраиваем маршрут
                if (potentialLength < currentLength) {
                    auto start = initialRoute.begin() + first;
                    auto end = initialRoute.begin() + second + 1;
                    reverse(start, end);
                    foundImprovement = true;
                }
            }
        }
    } while (foundImprovement);
    
    return initialRoute;
}
