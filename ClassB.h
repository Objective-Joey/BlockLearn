//
//  ClassB.h
//  BlockLearn
//
//  Created by WangPu on 2017/5/21.
//  Copyright © 2017年 WangPU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Handle.h"
#import "Logger.h"



@interface ClassB : NSObject

@property (strong) Handler * hand;
@property (strong) Logger * logger;

-(void)pring;
-(void)pring2;
@end
