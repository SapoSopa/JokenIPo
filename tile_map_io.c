//Essa parte quase toda eu só transcrevi pra cá mesmo, entendi pouco dessas funções, mas entendi que elas tão cortando um .png em tiles pra colocar nas sprites
#include "tile_map.h"
#include "sprites.h"

#include "libxml/parser.h"

const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;


void GetRelativeResource(const char* rootFile, const char* relFile, char* result)
{
	strcpy(result, rootFile);
	char* term = strrchr(result, '/');
	if (term != NULL)
		*term = '\0';
    strcat(result, "/");
    strcat(result, relFile);
}

bool ReadImageData(int *width, int *height, char *source, xmlNode *image)
{
	if (image.root() == NULL)
		return false;

	*width = image.attribute("width").as_int();
	*height = image.attribute("height").as_int();

	strcpy(source, image.attribute("source").as_string());

	if (strlen(source) > 0)
	{
		if (source[0] == '.')
		{
			char *firstSlash = strchr(source, '/');
			if (firstSlash != NULL)
				memmove(source, firstSlash + 1, strlen(firstSlash + 1) + 1);
		}
	}
	return true;
}

bool ReadTileSetNode(xmlNode *root, int idOffset, TileMap *map)
{
	float tileWidth = root.attribute("tilewidth").as_float();
	float tileHeight = root.attribute("tileheight").as_float();
	int tileCount = root.attribute("tilecount").as_int();
	int columCount = root.attribute("columns").as_int();
	int spacing = root.attribute("spacing").as_int();
	int margin = root.attribute("margin").as_int();
	xmlNode *child;
for (child = root->children; child; child = child->next)
{
    if (child->type == XML_ELEMENT_NODE)
    {
        const char *n = (const char *)child->name;
        if (strcmp(n, "tile") == 0)
        {
            xmlChar *idAttr = xmlGetProp(child, (const xmlChar *)"id");
            int id = atoi((const char *)idAttr);
            xmlFree(idAttr);
            int width, height;
            char source[100];
            xmlNode *imageNode = child->children;
            while (imageNode && strcmp((const char *)imageNode->name, "image") != 0)
                imageNode = imageNode->next;
            if (!ReadImageData(&width, &height, source, imageNode))
                continue;
        }
        else if (strcmp(n, "image") == 0)
        {
            int width, height;
            char source[100];
            ReadImageData(&width, &height, source, child);
        }
    }
}

	return true;
}

bool ReadTileSetFile(const char *tilesetFileName, int idOffset, TileMap *map)
{
	xmlDoc *doc = xmlReadFile(tilesetFileName, NULL, 0);
	if (doc == NULL)
        return false;

    xmlNode *root = xmlDocGetRootElement(doc);
    bool result = ReadTileSetNode(root, idOffset, map);

    xmlFreeDoc(doc);
    return result;
}

char** split(const char* str, char c, size_t* count)
{
    *count = 0;
    const char* s = str;
    while (*s != '\0')
    {
        if (*s == c)
            (*count)++;
        s++;
    }
    (*count)++;

    char** result = (char**)malloc((*count) * sizeof(char*));
    size_t i = 0;
    do
    {
        const char* begin = str;
        while (*str != c && *str)
            str++;

        result[i] = (char*)malloc(str - begin + 1);
        memcpy(result[i], begin, str - begin);
        result[i][str - begin] = '\0';
        i++;
    } while (0 != *str++);

    return result;
}

bool ReadObjectsLayer(xmlNode *root, TileMap *map)
{
    ObjectLayer *layerPtr = (ObjectLayer *)malloc(sizeof(ObjectLayer));
    memset(layerPtr, 0, sizeof(ObjectLayer));

    ObjectLayer *layer = layerPtr;
    xmlChar *idAttr = xmlGetProp(root, (const xmlChar *)"id");
    int id = atoi((const char *)idAttr);
    xmlFree(idAttr);

    layer->Id = id;
    xmlChar *nameAttr = xmlGetProp(root, (const xmlChar *)"name");
    strcpy(layer->Name, (const char *)nameAttr);
    xmlFree(nameAttr);

    for (xmlNode *child = root->children; child; child = child->next)
    {
        if (child->type == XML_ELEMENT_NODE)
        {
            const char *n = (const char *)child->name;
            if (strcmp(n, "object") == 0)
            {
                xmlChar *idAttr = xmlGetProp(child, (const xmlChar *)"id");
                int id = atoi((const char *)idAttr);
                xmlFree(idAttr);

                TileObject *object = NULL;

                if (child->children != NULL && strcmp((const char *)child->children->name, "polygon") == 0)
                {
                    TilePolygonObject *poly = (TilePolygonObject *)malloc(sizeof(TilePolygonObject));
                    memset(poly, 0, sizeof(TilePolygonObject));
                    object = (TileObject *)poly;
                }
                else if (child->children != NULL && strcmp((const char *)child->children->name, "text") == 0)
                {
                    TileTextObject *text = (TileTextObject *)malloc(sizeof(TileTextObject));
                    memset(text, 0, sizeof(TileTextObject));
                    object = (TileObject *)text;
                }
                else
                {
                    object = (TileObject *)malloc(sizeof(TileObject));
                    memset(object, 0, sizeof(TileObject));
                }
                layer->ObjectsCount++;
                layer->Objects = (TileObject **)realloc(layer->Objects, layer->ObjectsCount * sizeof(TileObject *));
                layer->Objects[layer->ObjectsCount - 1] = object;
            }
        }
    }

    map->LayersCount++;
    map->Layers = (Layer **)realloc(map->Layers, map->LayersCount * sizeof(Layer *));
    map->Layers[map->LayersCount - 1] = (Layer *)layerPtr;

    map->ObjectLayersCount++;
    map->ObjectLayers = (ObjectLayer **)realloc(map->ObjectLayers, map->ObjectLayersCount * sizeof(ObjectLayer *));
    map->ObjectLayers[map->ObjectLayersCount - 1] = layerPtr;

    return true;
}

bool ReadTiledXML(xmlDoc *doc, TileMap *map, const char *filePath)
{
	xmlNode *root = xmlDocGetRootElement(doc);

    xmlAttr *attr = root->properties;
    while (attr != NULL) {
        if (strcmp((char *)attr->name, "orientation") == 0) {
            if (strcmp((char *)attr->children->content, "orthogonal") == 0) {
                map->MapType = 0; // Orthographic
            } else {
                map->MapType = 1; // Isometric
            }
        }
        attr = attr->next;
    }

    xmlNode *child = root->children;
    while (child != NULL) {
        if (strcmp((char *)child->name, "tileset") == 0) {
            int idOffset = 0;
            xmlAttr *attr = child->properties;
            while (attr != NULL) {
                if (strcmp((char *)attr->name, "firstgid") == 0) {
                    idOffset = atoi((char *)attr->children->content);
                }
                attr = attr->next;
            }

            xmlNode *source = child->children;
            while (source != NULL && strcmp((char *)source->name, "source") != 0) {
                source = source->next;
            }

            if (source == NULL) {
                if (!ReadTileSetNode(child, idOffset, map)) {
                    return 0;
                }
            } else {
                char *tilesetFile = strdup((char *)source->children->content);
                if (!ReadTileSetFile(tilesetFile, idOffset, map)) {
                    return 0;
                }
                free(tilesetFile);
            }
        } else if (strcmp((char *)child->name, "properties") == 0) {
            xmlNode *prop = child->children;
            while (prop != NULL) {
                Property property;
                xmlAttr *attr = prop->properties;
                while (attr != NULL) {
                    if (strcmp((char *)attr->name, "name") == 0) {
                        property.Name = strdup((char *)attr->children->content);
                    } else if (strcmp((char *)attr->name, "type") == 0) {
                        property.Type = strdup((char *)attr->children->content);
                    } else if (strcmp((char *)attr->name, "value") == 0) {
                        property.Value = strdup((char *)attr->children->content);
                    }
                    attr = attr->next;
                }

                map->PropertiesSize++;
                map->Properties = realloc(map->Properties, map->PropertiesSize * sizeof(Property));
                map->Properties[map->PropertiesSize - 1] = property;

                prop = prop->next;
            }
        } else if (strcmp((char *)child->name, "objectgroup") == 0) {
            ReadObjectsLayer(child, map);
        } else if (strcmp((char *)child->name, "layer") == 0) {
            TileLayer *layer = malloc(sizeof(TileLayer));

            // ...

            map->TileLayersSize++;
            map->TileLayers = realloc(map->TileLayers, map->TileLayersSize * sizeof(TileLayer *));
            map->TileLayers[map->TileLayersSize - 1] = layer;
        }
        child = child->next;
    }

	return true;
}

bool ReadTileMap(const char *filename, TileMap *map)
{
	map->TileLayersSize = 0;
    free(map->TileLayers);
    map->TileLayers = NULL;

    map->ObjectLayersSize = 0;
    free(map->ObjectLayers);
    map->ObjectLayers = NULL;

    if (filename == NULL) {
        return 0;
    }

    xmlDoc *doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        return 0;
    }

    int result = ReadTiledXML(doc, map, filename);

    xmlFreeDoc(doc);

    return result;
}
