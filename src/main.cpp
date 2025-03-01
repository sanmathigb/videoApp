#include <stdio.h>
#include <GLFW/glfw3.h>

bool load_frame(const char* filename, int* widht, int* height, unsigned char** data);

int main (int argc, const char** argv){

    GLFWwindow* window;

    if(!glfwInit()){ 
        printf("could not do it");
        return 1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

/*     unsigned char* data = new unsigned char[100 * 100 * 3];
    for (int x = 0; x < 100; ++x)
    {
        for (int y = 0; y < 100; ++y)
        {
            data[x * 100 * 3 + y * 3     ] = 0xff;
            data[x * 100 * 3 + y * 3 + 1 ] = 0x00;
            data[x * 100 * 3 + y * 3 + 2 ] = 0x00;
        }
    }
    for (int x = 25; x < 75; ++x)
    {
        for (int y = 25; y < 75; ++y)
        {
            data[x * 100 * 3 + y * 3     ] = 0x00;
            data[x * 100 * 3 + y * 3 + 1 ] = 0x00;
            data[x * 100 * 3 + y * 3 + 2 ] = 0xff;
        }
    } */
    
    if(!window){
        printf("could not do it");
        return 1;
    }    

    int frame_width, frame_height;
    unsigned char* frame_data;
    if (!load_frame("/Users/Downloads/video_hq.mp4", &frame_width, &frame_height, &frame_data)){
        printf("Could not load frame");
        return 1;
    }

    // Create texture
    glfwMakeContextCurrent(window);
    GLuint tex_handle;
    frame_width = 100;
    frame_height = 100;
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, frame_data);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        //glBegin(GL_TRIANGLES);
        //glVertex2f(-0.5f, -0.5f);
        //glVertex2f( 0.0f, 0.5f);
        //glVertex2f( 0.5f, -0.5f);
        //glEnd();
        
        // Set up orphographic projection
        int window_width, window_height;
        glfwGetFramebufferSize(window, &window_width, &window_height);            
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window_width, 0, window_height, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        // Render whatver
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        glBegin(GL_QUADS);
            glTexCoord2d(0,0); glVertex2i(200,200);
            glTexCoord2d(1,0); glVertex2i(200 + frame_width,200);
            glTexCoord2d(1,1); glVertex2i(200 + frame_width,200 + frame_height);
            glTexCoord2d(0,1); glVertex2i(200,200 + frame_height);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
    return 0;
}