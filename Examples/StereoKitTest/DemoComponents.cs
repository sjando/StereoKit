﻿using StereoKit;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class DemoComponents : IScene
{
    EntityId floor;
    ComId<ComLifetimeChecker> lifetime;

    public void Initialize()
    {
        string root    = "../Examples/Assets/";
        Tex2D  cubemap = Tex2D.FromEquirectangular(root + "Sky/sky.hdr");
        Renderer.SetSkytex(cubemap);

        Material floorMat = new Material(Shader.Find("default/shader_pbr"));
        floorMat["diffuse"  ] = new Tex2D(root + "test.png");
        floorMat["normal"   ] = new Tex2D(root + "test_normal.png");
        floorMat["tex_scale"] = 6;

        Mesh m = Mesh.GenerateCube("app/mesh_cube", Vec3.One);
        //int x=0,y=0;
        for (int y = -10; y < 90; y++)
        {
            for (int x = -10; x < 90; x++)
            {
                floor = Entity.Create("Floor");
                floor.Add(new ComTransform(new Vec3(-x,0,-y)));
                floor.Add(new ComRender(m, floorMat));
                floor.Add(new ComScale());
            }
        }
        lifetime = floor.Add(new ComLifetimeChecker());
    }

    public void Shutdown()
    {
    }

    public void Update()
    {
        lifetime.Enabled = Input.Hand(Handed.Right).IsPinched;
        if (Input.Hand(Handed.Right).IsJustPinched)
        {
            floor.Find<ComLifetimeChecker>().Get().counter += 1;
        }
    }
}