//
//  ViewController.m
//  OpenGL_03
//
//  Created by 王鹏华 on 2017/6/22.
//  Copyright © 2017年 Hell. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
// openGL绘图上下文
@property (nonatomic, strong) EAGLContext *mContext;

@property (nonatomic, strong) GLKBaseEffect *effect;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [self configContext];
    [self configVertex];
    [self uploadTexture];
    
}
//在iOS上,只支持openGL2.0的绘图上下文.
- (void)configContext{
    
    self.mContext = [[EAGLContext alloc]initWithAPI:kEAGLRenderingAPIOpenGLES2];
    GLKView *view = (GLKView *)self.view;
    view.context = self.mContext;//指定绘图上下文
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    [EAGLContext setCurrentContext:self.mContext];
    
}

- (void)configVertex{
    //顶点数据,前三个是顶点坐标,后面两个是纹理坐标
    GLfloat squareVertexData[] = {
      // x    y   z     
        0.5,-0.5,0.0f,  1.0f,0.0f,//右下角
        0.5,0.5,0.0f,  1.0f,1.0f,//右上
        -0.5,0.5,0.0f,  0.0f,1.0f,//左上
        
        0.5,-0.5,0.0f,  1.0f,0.0f,//右下
        -0.5,0.5,0.0f,  0.0f,1.0f,//左上
        -0.5,-0.5,0.0f, 0.0f,0.0f,//左下
        
    };
    //顶点数据缓冲
    GLuint buffer;
    /*
     glGenBuffers (GLsizei n, GLuint* buffers);
     在buffers数组中返回当前n个未知顶点数据   buffers  表示缓冲区对象
     */
    glGenBuffers(1, &buffer); //设置缓冲  申请一个标识符
    /*
     GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer);
     target  GLenum枚举类型,指定缓冲区样式
     buffer  指定当前活动缓冲区对象
     */
    glBindBuffer(GL_ARRAY_BUFFER, buffer);//进行绑定  和标识符进行绑定
    /*
     GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
     target: 可以是GL_ARRAY_BUFFER()(顶点数据) 或 GL_ELEMENT_ARRAY_BUFFER (索引数据)
     size:  存储相关数据所需的内存容量
     data:  用于初始化缓冲区对象,可以是一个指向客户区内存的指针,也可以是NULL
     */
    //把顶点数据的内容从CPU复制到GPU的内存
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertexData), squareVertexData, GL_STATIC_DRAW);//对顶点缓存数据进行赋值
    //开启对应的顶点属性  因为OpenGL是一个状态机  需要什么状态就启动什么状态
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    /* 把数据传递给状态机(从buffer里面读取数据)
     1. 这里是顶点位置数据GLKVertexAttribPosition
     2. 数据的大小(每个点的数据个数,我们点的数据最多为xyz 为3 , xy 为2, xyz为三维坐标)
     3. 顶点的数据类型,我们定义的GLfloat数组所以是GL_FlOAT,如果用int定义顶点那么就是GL_INT....
     4. 一般都是GL_FALSE
     5. 跨度值,简单来讲,就是隔多少个值取一个点.假设为1(这个1不是真正的1,因为跨度是按内存空间来计算的)
        就是一个单位,那么我们就只能取到1,3,5...24被跨过去了.这个在使用顶点结构体的时间会有用,现在设为0
     6. 数据的地址,就是数组的名字
     */
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLfloat *)NULL + 0);
    
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);//纹理
    /*
     1. 把纹理数据传递给状态机
     */
    glVertexAttribPointer(GLKVertexAttribTexCoord0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLfloat *)NULL + 3);
    
}

- (void)uploadTexture{
    //纹理贴图
    NSString *filePath = [[NSBundle mainBundle]pathForResource:@"img" ofType:@"jpg"];
    //GLKTextureLoaderOriginBottomLeft  纹理坐标系是相反的
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1), GLKTextureLoaderOriginBottomLeft,nil];
    NSError *error;
    /*
     GLKTextureLoader 读取照片,创建纹理GLKTextureInfo
     创建着色器GLKBaseEffect,把纹理赋值给着色器
     */
    GLKTextureInfo *textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath options:options error:&error];
    
    if (error) {
        NSLog(@"%@",error);
    }
    
    self.effect = [[GLKBaseEffect alloc]init];
    self.effect.texture2d0.enabled = GL_TRUE;
    self.effect.texture2d0.name = textureInfo.name;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //设置背景布RGB色值以及透明度
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //启动着色器
    [self.effect prepareToDraw];
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
/*
 顶点数据 vs 索引数据
 顶点数据是需要清楚的知道每一个点的坐标,而索引数据是把顶点数据的坐标和索引进行绑定,然后用类似于[0,1,2,2,1,3]的方式去进行绘图
 顶点数据的绘图模式 列如:V0(0,0),V1(2,0),V2(1,2),V3(1,2),V4(2,0),V5(3,2)
 [(0,0),(2,0),(1,2),(1,2),(2,0),(3,2)]的方式去进行绘图
 */

@end
