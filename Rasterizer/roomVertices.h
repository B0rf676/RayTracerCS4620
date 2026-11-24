#pragma once

float roomVertices[] = {
    //Front Wall
    /*position*/ +1, +1, -1, /*uvs*/ 0, 0, /*normals*/ 0, 0, 1, //Vertex One
    /*position*/ -1, +1, -1, /*uvs*/ 1, 0, /*normals*/ 0, 0, 1, //Vertex Two
    /*position*/ +1, -1, -1, /*uvs*/ 1, 1, /*normals*/ 0, 0, 1, //Vertex Three

    /*position*/ -1, +1, -1, /*uvs*/ 1, 0, /*normals*/ 0, 0, 1, //Vertex One
    /*position*/ +1, -1, -1, /*uvs*/ 1, 1, /*normals*/ 0, 0, 1, //Vertex Two
    /*position*/ -1, -1, -1, /*uvs*/ 0, 0, /*normals*/ 0, 0, 1, //Vertex Three

    //Back Wall
    /*position*/ +1, +1, +1, /*uvs*/ 0, 0, /*normals*/ 0, 0, 1, //Vertex One
    /*position*/ -1, +1, +1, /*uvs*/ 1, 0, /*normals*/ 0, 0, 1, //Vertex Two
    /*position*/ +1, -1, +1, /*uvs*/ 1, 1, /*normals*/ 0, 0, 1, //Vertex Three

    /*position*/ -1, +1, +1, /*uvs*/ 1, 0, /*normals*/ 0, 0, 1, //Vertex One
    /*position*/ +1, -1, +1, /*uvs*/ 1, 1, /*normals*/ 0, 0, 1, //Vertex Two
    /*position*/ -1, -1, +1, /*uvs*/ 0, 0, /*normals*/ 0, 0, 1, //Vertex Three

    //Side Wall
    /*position*/-1, +1, +1,/* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex One
    /*position*/-1, +1, -1,/* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex Two
    /*position*/-1, -1, +1,/* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex Three
    
    /*position*/-1, +1, -1,/* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex One
    /*position*/-1, -1, +1,/* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex Two
    /*position*/-1, -1, -1,/* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex Three

    //Side Wall
    /*position*/+1, +1, +1,/* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex One
    /*position*/+1, +1, -1,/* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex Two
    /*position*/+1, -1, +1,/* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex Three
    
    /*position*/+1, +1, -1,/* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex One
    /*position*/+1, -1, +1,/* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex Two
    /*position*/+1, -1, -1,/* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex Three

};