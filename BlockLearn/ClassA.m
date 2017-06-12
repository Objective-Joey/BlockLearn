//
//  TestClass.m
//  BlockLearn
//
//  Created by WangPu on 2017/5/19.
//  Copyright © 2017年 WangPU. All rights reserved.
//

#import "ClassA.h"

typedef void(^BlockTest) (void);

@implementation ClassA


-(void )Test{

    __block NSMutableArray *arr1=[[NSMutableArray alloc] init];
    NSMutableArray *arr2=[[NSMutableArray alloc] init];


    _dic=[NSMutableDictionary new];
    [_dic setValue:@"fsdf" forKey:@"dfs"];

    BlockTest blk =[^{

        __strong ClassA * b=self;
        _dic=[[NSMutableDictionary alloc] initWithObjectsAndKeys:@"fsdfsd",@"dfsf" ,nil];
        int a=9;
        NSArray * arr=[[NSArray alloc] initWithObjects:@"Test", nil];
        NSLog(@"Block1\n___%@_____%@__%@",arr1,arr2,self);

    } copy];
 
    BlockTest blk2=^{
        
       NSLog(@"Block2\n___%@_____%@",arr1,arr2);
        
    };
}
@end
