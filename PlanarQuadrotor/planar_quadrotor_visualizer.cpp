#include "planar_quadrotor_visualizer.h"
PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    q_x = state[0];
    q_y = state[1];
    q_theta = state[2];

    float quadrotor_size[2] {150,20};
    float quadrotor_point1[2] {q_x-quadrotor_size[0]/2*(-cos(q_theta)),q_y-quadrotor_size[0]/2*sin(q_theta)};
    float quadrotor_point2[2] {q_x+quadrotor_size[0]/2*(-cos(q_theta)),q_y+quadrotor_size[0]/2*sin(q_theta)};
    
    float gowno_size[2] {40,8};  
    float gowno_L1[2] {quadrotor_point1[0],quadrotor_point1[1]};
    float gowno_L2[2] {quadrotor_point1[0]+gowno_size[0]*(-sin(q_theta)),quadrotor_point1[1]-gowno_size[0]*(cos(q_theta))};
    float gowno_R1[2] {quadrotor_point2[0],quadrotor_point2[1]};
    float gowno_R2[2] {quadrotor_point2[0]+gowno_size[0]*(-sin(q_theta)),quadrotor_point2[1]-gowno_size[0]*(cos(q_theta))};

    float prop_size[3] {30,15,0};
    float prop_current[2] {0,10};

    if(SDL_GetTicks()%500<100)prop_current[0]={prop_size[0]};
    else if(SDL_GetTicks()%500<200)prop_current[0]={prop_size[1]};
    else if(SDL_GetTicks()%500<300)prop_current[0]={prop_size[2]};
    else if(SDL_GetTicks()%500<400)prop_current[0]={prop_size[1]};
    else prop_current[0]={prop_size[0]};


    ellipseColor(gRenderer.get(),gowno_L2[0]+prop_current[0],gowno_L2[1],prop_current[0],prop_current[1],0xFF000000);
    ellipseColor(gRenderer.get(),gowno_L2[0]-prop_current[0],gowno_L2[1],prop_current[0],prop_current[1],0xFF000000);
    ellipseColor(gRenderer.get(),gowno_R2[0]+prop_current[0],gowno_R2[1],prop_current[0],prop_current[1],0xFF000000);
    ellipseColor(gRenderer.get(),gowno_R2[0]-prop_current[0],gowno_R2[1],prop_current[0],prop_current[1],0xFF000000);

    thickLineColor(gRenderer.get(),quadrotor_point1[0],quadrotor_point1[1],quadrotor_point2[0],quadrotor_point2[1],quadrotor_size[1],0xFFFF00FF);
    thickLineColor(gRenderer.get(),gowno_L1[0],gowno_L1[1],gowno_L2[0],gowno_L2[1],gowno_size[1],0xFF00FF00);
    thickLineColor(gRenderer.get(),gowno_R1[0],gowno_R1[1],gowno_R2[0],gowno_R2[1],gowno_size[1],0xFF00FF00);

    //SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xFF, 0x00, 0xFF);
   // filledCircleColor(gRenderer.get(), q_x, q_y, 30, 0xFFFF00FF);
}