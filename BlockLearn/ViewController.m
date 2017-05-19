//
//  ViewController.m
//  BlockLearn
//
//  Created by WangPu on 2017/5/17.
//  Copyright © 2017年 WangPU. All rights reserved.
//

#import "ViewController.h"

typedef void (^BlockObj)(void);

@interface ViewController ()

@property BlockObj obj7;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    //Block 形式上类似于函数指针
    //本质上是对象
    //使用方法上和普通的对象没区别

    NSArray * arr1=[[NSArray alloc] initWithObjects:@"Test1", nil];
    
    BlockObj block1=^{
        
        NSLog(@"block1__%@",arr1);
    };
    BlockObj block2=^{
        
        NSLog(@"block2__%@",arr1);
    };
    
    block1();
    block2();
    //问题一
    //执行Block语法时，Block语法表达式所使用的自动变量值被保存到Block结构体实例中。
    //因此block1、block2各自持有arr1的copy
    //注意，虽然block1是局部变量，但是不是NSStackBlock类型
    //而是NSMallocBlock类型
    //因为ARC有效时，自动生成将Block对象复制到堆上的代码。
    
    __block NSArray * arr2=[[NSArray alloc] initWithObjects:@"Test2", nil];
    
    BlockObj block3=^{
        
        NSLog(@"block3__%@",arr2);
    };
    BlockObj block4=^{
        
        NSLog(@"block4__%@",arr2);
    };
    block3();
    arr2=[[NSArray alloc] initWithObjects:@"ValueChanged", nil ];
    block4();
    //问题二
    //被__block修饰的变量被转换为结构体变量，Block持有该结构体的指针
    //因为arr2被转换为结构体，此结构体持有arr2的强引用。block3、block4只是持有指向arr2结构体的指针

    BlockObj block5;
    {
    
       NSArray *arr=[[NSArray alloc] initWithObjects:@"test5", nil ];
        
        NSArray * __weak temp=arr;
        
        block5=^{
            
            NSLog(@"block5__%@",temp);
        };
    }
    block5();
    //问题三
    // ARC 有效时。变量默认是被__strong修饰符修饰
    // id test=[[NSObject alloc] init]; 等价于
    //  id __strong test=[[NSObject alloc] init];
    // block5 只是弱引用 arr，arr超出其作用域，被释放，因此temp被置为null。
    
    BlockObj block6;
    {
        
        NSArray *arr=[[NSArray alloc] initWithObjects:@"test5", nil ];
        
       __block NSArray * __weak temp=arr;
        
        block6=^{
            
            NSLog(@"block6____%@",temp);
        };
    }
    block6();
    //问题三
    //同问题二，temp被编译成结构体，持有arr的弱引用
    //block6持有temp被编译成结构体后的指针
    //arr超出其作用域，被释放，因此temp被置为null。

    _obj7=block6;
    
   //问题四
    //属性默认为__strong修饰符修饰
    //因此不用指明copy来修饰
    
    UIButton *btn=[[UIButton alloc] initWithFrame:CGRectMake(40, 40, 100, 100)];
    btn.backgroundColor=[UIColor redColor];
    [btn addTarget:self action:@selector(question4) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];

    // Do any additional setup after loading the view, typically from a nib.
}
//问题四
//属性默认为__strong修饰符修饰
//因此不用指明copy来修饰
-(void)question4{

    _obj7();
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
 
    
    // Dispose of any resources that can be recreated.
}


@end
