/* 
 * File:   Towers.cpp
 * Author: gabriel
 * 
 * Created on 14 de Abril de 2011, 17:53
 */

#include "Towers.h"
#include "externs.h"
#include "GLManager.h"
#include "Map.h"

Towers::Towers(const string &path) {

    num_towers = conf.rint("game:num_towers");
    float towers_min_distance = conf.rfloat("game:towers_min_distance");

    towers = (Tower **) calloc(num_towers, sizeof (Tower*));

    for (int i = 0; i < num_towers; i++) {
        towers[i] = new Tower(i, path);
        Vertex* pos = NULL;
        do {
        	pos = GLManager::randomVertex();
        	for(int j = 0; j < i && pos != NULL; j++) {
        		if (pos->distance(towers[i]->coords) < towers_min_distance)
        			pos = NULL;
        	}
        } while(pos == NULL);

		pos->y = g_map->triangulateHeight(pos->x, pos->z);
        towers[i]->set_pos(pos);
    }

}

int Towers::get_closest_distance() {
    int distance = 9999999;
    for (int i = 0; i < num_towers; i++) {
        if (towers[i]->dir_dist < distance) {
            distance = towers[i]->dir_dist;
        }
    }
    return distance;
}

void Towers::render() {
    for (int i = 0; i < num_towers; i++) {
        towers[i]->render();
    }
}

void Towers::update() {
	for (int i = 0; i < num_towers; i++) {
		towers[i]->update();
	}
}