#include <iostream>
#include <vector>

#include "Graph.hpp"

int main()
{
    std::cout << "FORESTER v0.1\n";
    std::cout << "\nBase graph properties\n";

    /*std::cout << "Degree (number of nodes): ";
    const int degree = [](){
        int temp = 0;
        std::cin >> temp;
        return temp;
    }();

    std::cout << "Size (number of edges): ";
    const int edges = [](){
        int temp = 0;
        std::cin >> temp;
        return temp;
    }();

    std::cout << "\nHamilton properties\n";

    std::cout << "Existence of Hamilton route [y,N]: ";
    const bool hamiltonRoute = [](){
        char temp = 'N';
        std::cin >> temp;
        return temp == 'y';
    }();

    if (hamiltonRoute)
    {
        std::cout << "Existence of Hamilton circle [y,N]: ";
        const bool hamiltonCircle = [](){
            char temp = 'N';
            std::cin >> temp;
            return temp == 'y';
        }();
    }*/

    std::vector<bool> row1({false, true, true, true});
    std::vector<bool> row2({true, false, true, true});
    std::vector<bool> row3({true, true, false, true});
    std::vector<bool> row4({true, true, true, false});
    std::vector<std::vector<bool>> matrix({row1, row2, row3, row4});

    Graph graph(matrix);

    std::cout << "Degree: " << graph.getDegree() << std::endl;
    std::cout << "Size: " << graph.getSize() << std::endl;
    std::cout << "Complete: " << (graph.isComplete() ? "Yes" : "No") << std::endl;
    std::cout << "Continuous: " << (graph.isContinuous() ? "Yes" : "No") << std::endl;
    if (graph.isContinuous())
    {
        std::cout << "Locally continuous: " << (graph.isLocallyContinuous() ? "Yes" : "No") << std::endl;
        std::cout << "Node continuity: " << graph.getNodeContinuity() << std::endl;
        std::cout << "Edge continuity: " << graph.getEdgeContinuity() << std::endl;
    }
    std::cout << "Has claw (K13): " << (graph.hasClaw() ? "Yes" : "No") << std::endl;
    std::cout << "Hamilton route: " << (graph.hasHamiltonRoute() ? "Yes" : "No") << std::endl;
    if (graph.hasHamiltonRoute())
    {
        std::cout << "Hamilton circle: " << (graph.hasHamiltonCircle() ? "Yes" : "No") << std::endl;
    }
    std::cout << "Circumference: " << graph.getCircumference() << std::endl;

    return 0;
}
