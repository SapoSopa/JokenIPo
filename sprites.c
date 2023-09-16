#include "include/sprites.h"
#include <stdlib.h>
#include <stdio.h>
#include <tmx.h>
#include <raylib.h>
#include <string.h>

// #define ANIMATION

void *raylib_tex_loader(const char *path) {
	Texture2D *returnValue = malloc(sizeof(Texture2D));
	*returnValue = LoadTexture(path);
	return returnValue;
}

void raylib_free_tex(void *ptr) {
	UnloadTexture(*((Texture2D *) ptr));
	free(ptr);
}

Color int_to_color(int color) {
	tmx_col_bytes res = tmx_col_to_bytes(color);
	return *((Color*)&res);
}

void draw_polyline(double offset_x, double offset_y, double **points, int points_count, Color color) {
	int i;
	for (i=1; i<points_count; i++) {
		DrawLineEx((Vector2){offset_x + points[i-1][0], offset_y + points[i-1][1]},
		           (Vector2){offset_x + points[i][0], offset_y + points[i][1]},
		           LINE_THICKNESS, color);
	}
}

void draw_polygon(double offset_x, double offset_y, double **points, int points_count, Color color) {
	draw_polyline(offset_x, offset_y, points, points_count, color);
	if (points_count > 2) {
		DrawLineEx((Vector2){offset_x + points[0][0], offset_y + points[0][1]},
		           (Vector2){offset_x + points[points_count-1][0], offset_y + points[points_count-1][1]},
		           LINE_THICKNESS, color);
	}
}

void draw_objects(tmx_object_group *objgr) {
	tmx_object *head = objgr->head;
	Color color = int_to_color(objgr->color);

	while (head) {
		if (head->visible) {
			if (head->obj_type == OT_SQUARE) {
				DrawRectangleLinesEx((Rectangle){head->x, head->y, head->width, head->height}, LINE_THICKNESS, color);
			}
			else if (head->obj_type  == OT_POLYGON) {
				draw_polygon(head->x, head->y, head->content.shape->points, head->content.shape->points_len, color);
			}
			else if (head->obj_type == OT_POLYLINE) {
				draw_polyline(head->x, head->y, head->content.shape->points, head->content.shape->points_len, color);
			}
			else if (head->obj_type == OT_ELLIPSE) {
				DrawEllipseLines(head->x + head->width/2.0, head->y + head->height/2.0, head->width/2.0, head->height/2.0, color);
			}
		}
		head = head->next;
	}
}

void draw_image_layer(tmx_image *image) {
	Texture2D *texture = (Texture2D*)image->resource_image;
	DrawTexture(*texture, 0, 0, WHITE);
}

void draw_tile(void *image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
               unsigned int dx, unsigned int dy, float opacity, unsigned int flags) {
    Texture2D *texture = (Texture2D*)image;
    int op = 0xFF * opacity;
    DrawTextureRec(*texture, (Rectangle) {sx, sy, sw, sh}, (Vector2) {dx, dy}, (Color) {op, op, op, op});
}

void draw_layer(tmx_map *map, tmx_layer *layer) {
	unsigned long i, j;
	unsigned int gid, animLen = 0, x, y, w, h, flags;
	float op;
	tmx_tileset *ts;
	tmx_image *im;
	tmx_anim_frame *anim;
	void* image;
	op = layer->opacity;
	tmx_tile *nextTile;

	static float timeCounter = 0;
	timeCounter += GetFrameTime();

	if (timeCounter > 1e8) {
		timeCounter = 0;
	}

	for (i=0; i<map->height; i++) {
		for (j=0; j<map->width; j++) {
			gid = (layer->content.gids[(i*map->width)+j]) & TMX_FLIP_BITS_REMOVAL;
			nextTile = map->tiles[gid];
			//printf("AnimGid before: %d\n", gid);

			if (nextTile == NULL)  continue; 

			im = nextTile->image;
			anim = nextTile->animation;
			animLen = nextTile->animation_len;
			tmx_tileset *myTs = nextTile->tileset;

            #ifdef ANIMATION
			if (animLen > 0 && !im) {

				printf("FrameTime: %f\n", GetFrameTime());
				printf("My timeCounter: %f\n", timeCounter);
				printf("My duration: %d\n", anim->duration); 
				int myFrame = (int)((int) ((timeCounter*1000) / (anim->duration))) % (animLen);

				unsigned int AnimGid = (anim[myFrame].tile_id) & TMX_FLIP_BITS_REMOVAL;
 				printf("AnimGid: %d\n", AnimGid);
				printf("My animation Lenght: %d\n", animLen);
				printf("My frame: %d\n", myFrame); 
				
				if ((myTs->tiles) + AnimGid == NULL) {
					printf("NULL tile\n");
				}
				else {
					nextTile = (myTs->tiles) + AnimGid;
				}
			}
            #endif

			x  = nextTile->ul_x;
			y  = nextTile->ul_y;
			w  = myTs->tile_width;
			h  = myTs->tile_height;

			if (im) {
				image = im->resource_image;
			}
			else {
				image = myTs->image->resource_image;
			}

			flags = (layer->content.gids[(i*map->width)+j]) & ~TMX_FLIP_BITS_REMOVAL;
			draw_tile(image, x, y, w, h, j*myTs->tile_width, i*myTs->tile_height, op, flags);
		}
	}
}

void draw_all_layers(tmx_map *map, tmx_layer *layers) {
	while (layers) {
		if (layers->visible) {
			if (layers->type == L_GROUP) {
				draw_all_layers(map, layers->content.group_head); // recursive call
			}
			else if (layers->type == L_OBJGR) {
				draw_objects(layers->content.objgr);
			}
			else if (layers->type == L_IMAGE) {
				draw_image_layer(layers->content.image);
			}
			else if (layers->type == L_LAYER) {
				draw_layer(map, layers);
			}
		}
		layers = layers->next;
	}
}

void render_map(tmx_map *map) {
	ClearBackground(int_to_color(map->backgroundcolor));
	draw_all_layers(map, map->ly_head);
}
