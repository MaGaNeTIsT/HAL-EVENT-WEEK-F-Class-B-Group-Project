#ifndef _COMMON_H
#define _COMMON_H

#define SAFE_RELEASE(x) {if(x) { (x)->Release(); (x) = NULL;}}
#define SAFE_DELETE(x) {if((x) != NULL) { delete (x); (x) = NULL;}}
#define PTR_DELETE(x) {if((x) != NULL) { delete (x); (x) = NULL;}}

#define CLASS_NAME                      "GAMEWindow"
#define WINDOW_CAPTION                  "GAMEWindow"

#define WINDOW_WIDTH                    (1920)
#define WINDOW_HEIGHT                   (1080)

#define FVF_VERTEX2D                    (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define TEXTURE_COUNT                   (20)
#define TEXTURE_FPS_COUNT               (10)

#endif // !_COMMON_H