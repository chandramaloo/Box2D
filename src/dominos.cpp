/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 251 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * 
 */

#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251
{
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  
  dominos_t::dominos_t()
  {
    //Ground
    /*! \var b1 
     * \brief pointer to the body ground 
     */ 
    b2Body* b1;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
         
    //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(20.0f, 0.25f);	

      b2BodyDef bd;
      bd.position.Set(+0.0f, 40.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
    	  b2PolygonShape shape;
      shape.SetAsBox(2.0f, 0.25f);	

      b2BodyDef bd;
      bd.position.Set(-16.6f, 38.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    	//pendulum
    		b2Body* sbody;
			b2CircleShape circle;
			circle.m_radius = 0.5;
	
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 10.0f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.6f;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set(-16.6f, 32.2f);
			sbody = m_world->CreateBody(&ballbd);
			sbody->CreateFixture(&ballfd);

			b2RopeJointDef jointDef;
			jointDef.bodyA = ground;
	 		jointDef.bodyB = sbody;
   		jointDef.localAnchorA = b2Vec2(0.0f, 0.0f);
   		jointDef.localAnchorB = b2Vec2(0.0f,0.0f);
   		jointDef.maxLength = 5.8f;
   		jointDef.collideConnected = false;
   		m_world->CreateJoint(&jointDef);
    }
    //Vertical bar
    {
    	b2PolygonShape shape;
      shape.SetAsBox(0.02f, 19.5f);	

      b2BodyDef bd1;
      bd1.type = b2_dynamicBody;	
      bd1.position.Set(21.0f, 22.75f);
      b2Body* ground1 = m_world->CreateBody(&bd1);
      ground1->CreateFixture(&shape, 0.0f);
    }
    //Another shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.0f, 0.10f);
      b2BodyDef bd;
      bd.position.Set(24.0f, 40.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    // Alarm Clock
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 0.50f);
      b2BodyDef bd;
      bd.type = b2_dynamicBody;	
      bd.position.Set(21.0f, 2.5f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {		//handle1
      b2PolygonShape shape;
      shape.SetAsBox(0.05f, 1.0f);
      b2BodyDef bd;
      bd.type = b2_dynamicBody;	
      bd.position.Set(21.5f, 1.1f);
      b2Body* ground = m_world->CreateBody(&bd);
      b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 1.0f;
			fd3->friction = 4.99f;
			fd3->shape = new b2PolygonShape;
			fd3->shape = &shape;
			ground->SetTransform( ground->GetPosition(), 10.0f );
			ground->CreateFixture(fd3);
	  }
	  {	//handle2
      b2PolygonShape shape;
      shape.SetAsBox(0.05f, 1.0f);
      b2BodyDef bd;
      bd.type = b2_dynamicBody;	
      bd.position.Set(20.5f, 1.1f);
      b2Body* ground = m_world->CreateBody(&bd);
      b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 1.0f;
			fd3->friction = 4.99f;
			fd3->shape = new b2PolygonShape;
			fd3->shape = &shape;
			ground->SetTransform( ground->GetPosition(), -10.0f );
			ground->CreateFixture(fd3);
	  }
	  //Initiator
	  {	
	  	     b2PolygonShape shape;
      shape.SetAsBox(2.5f, 0.01f);
      b2BodyDef bd;
      bd.type = b2_dynamicBody;	
      bd.position.Set(21.5f, 42.5f);
      b2Body* ground = m_world->CreateBody(&bd);
      b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 1000.0f;
			fd3->friction = 4.5f;
			fd3->shape = new b2PolygonShape;
			fd3->shape = &shape;
			ground->SetTransform( ground->GetPosition(), -10.0f );
			ground->CreateFixture(fd3);

	  }

    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 2000.0f;
      fd.friction = 0.1f;
		
	    for (int i = 0; i < 10; ++i)
			{
			  b2BodyDef bd;
			  bd.type = b2_dynamicBody;
			  bd.position.Set(10.f + 1.0f * i, 41.25f);
			  b2Body* body = m_world->CreateBody(&bd);
			  body->CreateFixture(&fd);
			}
    }
		// First ball
		{
			b2Body* sbody;
			b2CircleShape circle;
			circle.m_radius = 0.5;
	
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 50.0f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.6f;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set(7.75f, 41.0f);
			sbody = m_world->CreateBody(&ballbd);
			sbody->CreateFixture(&ballfd);
		}    
    //Ball redirection machinery
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.0f, 0.10f);
      b2BodyDef bd;
      bd.position.Set(-24.0f, 32.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.10f, 4.0f);
      b2BodyDef bd;
      bd.position.Set(-25.5f, 35.5f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    // ball on platform
    {
    	  b2PolygonShape shape;
      shape.SetAsBox(1.0f, 0.025f);	

      b2BodyDef bd;
      bd.position.Set(-11.5f, 33.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);

    		b2Body* sbody;
			b2CircleShape circle;
			circle.m_radius = 0.5;
	
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 1.0f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.5f;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set(-12.2f, 33.5f);
			sbody = m_world->CreateBody(&ballbd);
			sbody->CreateFixture(&ballfd);
		}
  	//The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(8,20);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(1.5,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      //(width, height, x-coord, y-coord)
      bs2.SetAsBox(0.01,2, b2Vec2(1.5f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 1.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.01,2, b2Vec2(-1.5f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(-8,20);	
      fd1->density = 0.50;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);
      box2->CreateFixture(fd2);
      box2->CreateFixture(fd3);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(8, 20); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(-8, 20); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(8, 25); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(-8, 25); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
    //Water :D
    {
 			b2CircleShape circle;
			circle.m_radius = 0.05;
	
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = .01f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.5f;
			
	    for (int i = 0; i < 200; ++i)
			{
				b2BodyDef ballbd;
				ballbd.type = b2_dynamicBody;
				ballbd.position.Set(7.55f + 1.0f * i/200, 20.f);
			  b2Body* body = m_world->CreateBody(&ballbd);
			  body->CreateFixture(&ballfd);
			}
    }
  }
  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
