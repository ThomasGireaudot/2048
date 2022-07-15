/*
** EPITECH PROJECT, 2022
** arcade_2048
** File description:
** MyRayLib
*/

#ifndef _arcade_2048
#define _arcade_2048

#include "raylib.h"
#include "rlgl.h"

class MyRayLib {
    public:
        static void myInitWindow(int width, int height, const char *title)
        {
            InitWindow(width, height, title);
        }
        static RLAPI void myRlDisableBackfaceCulling(void)
        {
            rlDisableBackfaceCulling();
        }
        static void mySetCameraMode(Camera camera, int mode)
        {
            SetCameraMode(camera, mode);
        }
        static bool myDirectoryExists(const char *dirPath)
        {
            return (DirectoryExists(dirPath));
        }
        static bool myFileExists(const char *fileName)
        {
            return (FileExists(fileName));
        }
        static char *myLoadFileText(const char *fileName)
        {
            return (LoadFileText(fileName));
        }
        static void mySetTargetFPS(int fps)
        {
            SetTargetFPS(fps);
        }
        static bool myWindowShouldClose(void)
        {
            return (WindowShouldClose());
        }
        static bool myIsKeyPressed(int key)
        {
            return (IsKeyPressed(key));
        }
        static bool mySaveFileText(const char *fileName, char *text)
        {
            return (SaveFileText(fileName, text));
        }
        static bool myCheckCollisionPointRec(Vector2 point, Rectangle rec)
        {
            return (CheckCollisionPointRec(point, rec));
        }
        static Vector2 myGetMousePosition(void)
        {
            return (GetMousePosition());
        }
        static bool myIsMouseButtonPressed(int button)
        {
            return (IsMouseButtonPressed(button));
        }
        static void mySetMouseCursor(int cursor)
        {
            SetMouseCursor(cursor);
        }
        static int myGetCharPressed(void)
        {
            return (GetCharPressed());
        }
        static float myGetMouseWheelMove(void)
        {
            return (GetMouseWheelMove());
        }
        static void myUpdateCamera(Camera *camera)
        {
            UpdateCamera(camera);
        }
        static void myBeginDrawing(void)
        {
            BeginDrawing();
        }
        static void myClearBackground(Color color)
        {
            ClearBackground(color);
        }
        static void myBeginMode3D(Camera3D camera)
        {
            BeginMode3D(camera);
        }
        static void myDrawGrid(int slices, float spacing)
        {
            DrawGrid(slices, spacing);
        }
        static void myEndMode3D(void)
        {
            EndMode3D();
        }
        static void myDrawRectangle(int posX, int posY, int width, int height, Color color)
        {
            DrawRectangle(posX, posY, width, height, color);
        }
        static void myDrawRectangleRec(Rectangle rec, Color color)
        {
            DrawRectangleRec(rec, color);
        }
        static void myDrawText(const char *text, int posX, int posY, int fontSize, Color color)
        {
            DrawText(text, posX, posY, fontSize, color);
        }
        static int myMeasureText(const char *text, int fontSize)
        {
            return (MeasureText(text, fontSize));
        }
        static void myBeginScissorMode(int x, int y, int width, int height)
        {
            BeginScissorMode(x, y, width, height);
        }
        static void myEndScissorMode(void)
        {
            EndScissorMode();
        }
        static void myEndDrawing(void)
        {
            EndDrawing();
        }
        static void myCloseWindow(void)
        {
            CloseWindow();
        }
        static void mySetMaterialTexture(Material *material, int mapType, Texture2D texture)
        {
            SetMaterialTexture(material, mapType, texture);
        }
        static void mySetModelMeshMaterial(Model *model, int meshId, int materialId)
        {
            SetModelMeshMaterial(model, meshId, materialId);
        }
        static void myDrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint)
        {
            DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
        }
        static char **myGetDirectoryFiles(const char *dirPath, int *count)
        {
            return (GetDirectoryFiles(dirPath, count));
        }
        static bool myIsFileExtension(const char *fileName, const char *ext)
        {
            return (fileName, ext);
        }
        static Model myLoadModel(const char *fileName)
        {
            return (LoadModel(fileName));
        }
        static Texture2D myLoadTexture(const char *fileName)
        {
            return (LoadTexture(fileName));
        }
        static void myDrawCube(Vector3 position, float width, float height, float length, Color color)
        {
            DrawCube(position, width, height, length, color);
        }
        static void myDrawSphere(Vector3 centerPos, float radius, Color color)
        {
            DrawSphere(centerPos, radius, color);
        }
        static void myDrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color)
        {
            DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
        }
        static bool myCheckCollisionBoxSphere(BoundingBox base, Vector3 position, float radius)
        {
            return (CheckCollisionBoxSphere(base, position, radius));
        }
        static void myToggleFullscreen()
        {
            ToggleFullscreen();
        }
        static void myDrawRectangleLines(int posX, int posY, int width, int height, Color color)
        {
            DrawRectangleLines(posX, posY, width, height, color);
        }
};

#endif