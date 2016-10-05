//
//  main.cpp
//  Integer Programming
//
//  Created by Aurelien on 03/10/2016.
//  Copyright © 2016 Aurelien. All rights reserved.
//

using namespace std;

#include <iostream>
#include <stdio.h>
#include <vector>
#include <iostream>


struct Node {
    int object;
    int weight;
    int profit;
    int posBest;
};

int main(int argc, const char * argv[]) {

    
    

    int nbObj = 4;
    
    int capacity = 4;
    vector<int> profits = {2,1,3,2};
    vector<int> weights = {2,3,4,2};
    
//    int capacity = 3;
//    vector<int> profits = {4,5,10,3};
//    vector<int> weights = {2,4,7,3};

    int nbNodes = (capacity + 1) * nbObj;
    vector<Node> listNodes(nbNodes);
    
    int compteur = 0;
    for (int i = 1; i <= nbObj; i++) {
        for (int j = 0; j <= capacity; j++) {
            Node n = {i, j, 0, 0};
            listNodes[compteur] = n;
            compteur += 1;
        }
    }
    
    
    // assurer que le poids de départ du noeud ne dépasse pas la capacité d
    vector<Node> actifNodes = {listNodes[0], listNodes[weights[0]]};
    listNodes[weights[0]].profit = profits[0];
    
    while (actifNodes.size() != 0) {
        
        /* On prend le premier élément de la liste des noeuds actifs */
        
        int arcWeight = weights[actifNodes[0].object] + actifNodes[0].weight;
        int profit = profits[actifNodes[0].object];
        int positionActive = (actifNodes[0].object - 1) * (capacity+1) + actifNodes[0].weight;
        
        //cout << "Objet (" << actifNodes[0].object << "," << actifNodes[0].weight << ")" << endl;
        
        if (actifNodes[0].object < nbObj) {
            
            /* Premier sommet adjacent, décision de ne pas prendre */
            int position_1 = (capacity + 1) * actifNodes[0].object + actifNodes[0].weight;
            actifNodes.push_back(listNodes[position_1]);
            //cout << "Création de : Objet (" << listNodes[position_1].object << "," << listNodes[position_1].weight << ")" << endl;
            
            //cout << listNodes[positionActive].profit << " vs " << listNodes[position_1].profit << endl;
            if (listNodes[positionActive].profit > listNodes[position_1].profit) {
                listNodes[position_1].profit = listNodes[positionActive].profit;
                listNodes[position_1].posBest = positionActive;
            }
            
            /* Second sommet adjacent, décision de prendre cet objet, on MAJ le profit */
            if (arcWeight <= capacity) {
                
                
                int position_2 = ((capacity + 1) * actifNodes[0].object) + arcWeight;
                
                //cout << "Création de : Objet (" << listNodes[position_2].object << "," << listNodes[position_2].weight << ")" << endl;

                if (listNodes[positionActive].profit + profit > listNodes[position_2].profit) {
                    listNodes[position_2].profit = profit + listNodes[positionActive].profit;
                    listNodes[position_2].posBest = positionActive;

                }
                actifNodes.push_back(listNodes[position_2]);

                
            }
        }
        
        actifNodes.erase(actifNodes.begin());
        
    }
    
    cout << "-------------" << endl;
    for (auto elt : listNodes) {
        
        cout << "Objet (" << elt.object << "," << elt.weight << ")" << " avec profit de : " << elt.profit << endl;
    }
    
    Node bestNode = listNodes[0];
    for (int i = (capacity+1) * (nbObj-1); i < listNodes.size(); i++) {
        if (listNodes[i].profit > bestNode.profit) {
            bestNode = listNodes[i];
        }
    }
    cout << "-------------" << endl;
    cout << "Best node (" << bestNode.object << "," << bestNode.weight << ")" << " avec profit de : " << bestNode.profit << endl;
    
    int position = bestNode.posBest;
    int profit = bestNode.profit;
    for (int i = 0; i < nbObj - 1; i++) {
        
        if (profit > listNodes[position].profit) {
            cout << "Je prend objet : " << listNodes[position].object + 1 << endl;
        }
        
        else {
            cout << "Je prend pas objet : " << listNodes[position].object + 1 << endl;

        }
        
        profit = listNodes[position].profit;
        position = listNodes[position].posBest;
    }
    
    if (profit > listNodes[position].profit) {
        cout << "Je prend objet : " << listNodes[position].object << endl;
    }
    
    else {
        cout << "Je prend pas objet : " << listNodes[position].object << endl;
        
    }
    
    
    
    return 0;
}
