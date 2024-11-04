#include "MeshImporter.h"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

Mesh MeshImporter::getCube()
{
    return  Mesh{
           {
            //front
            {{-0.5f, -0.5f, 0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f,  0.5f, 0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f}},
            {{ 0.5f,  0.5f, 0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f}},
            {{ 0.5f, -0.5f, 0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 0.0f, 1.0f}},

            //back	  
            {{ 0.5f, -0.5f,-0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, -1.0f}},
            {{ 0.5f,  0.5f,-0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, -1.0f}},
            {{-0.5f,  0.5f,-0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, -1.0f}},
            {{-0.5f, -0.5f,-0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 0.0f, -1.0f}},

            //left
            {{-0.5f, -0.5f, -0.5f},	{0.0f,0.5f,0.1f,1.0f}, {-1.0f, 0.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f},	{1.0f,0.5f,0.1f,1.0f}, {-1.0f, 0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f},	{0.5f,0.5f,0.1f,1.0f}, {-1.0f, 0.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f},	{0.0f,0.5f,1.0f,1.0f}, {-1.0f, 0.0f, 0.0f}},

            //right
            {{0.5f, -0.5f,  0.5f},	{0.0f,0.5f,0.1f,1.0f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f},	{1.0f,0.5f,0.1f,1.0f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f},	{0.5f,0.5f,0.1f,1.0f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f},	{0.0f,0.5f,1.0f,1.0f}, {1.0f, 0.0f, 0.0f}},

            //top
            {{-0.5f, 0.5f,  0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 1.0f, 0.0f}},
            {{ 0.5f, 0.5f, -0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 1.0f, 0.0f}},
            {{ 0.5f, 0.5f,  0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 1.0f, 0.0f}},

            //bottom
            {{-0.5f, -0.5f, -0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, -1.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, -1.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, -1.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, -1.0f, 0.0f}},
        },
        {
            0,3,2,0,2,1,
            0 + 4,3 + 4,2 + 4,0 + 4,2 + 4,1 + 4,
            0 + 8,3 + 8,2 + 8,0 + 8,2 + 8,1 + 8,
            0 + 12,3 + 12,2 + 12,0 + 12,2 + 12,1 + 12,
            0 + 16,3 + 16,2 + 16,0 + 16,2 + 16,1 + 16,
            0 + 20,3 + 20,2 + 20,0 + 20,2 + 20,1 + 20,
        }
    };
}
//
//std::optional<Mesh> MeshImporter::importFile(const std::string& pFile) {
//    // Create an instance of the Importer class
//    Assimp::Importer importer;
//
//    // And have it read the given file with some example postprocessing
//    // Usually - if speed is not the most important aspect for you - you'll
//    // probably to request more postprocessing than we do in this example.
//    const aiScene* pScene = importer.ReadFile(pFile,
//        //      aiProcess_CalcTangentSpace |
//        aiProcess_Triangulate |
//        aiProcess_JoinIdenticalVertices |
//        aiProcess_SortByPType);
//
//    // If the import failed, report it
//    if (!pScene) {
//        return std::nullopt;
//    }
//
//    return model;
//}