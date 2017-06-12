//
//  Handle.h
//  BlockLearn
//
//  Created by WangPu on 2017/5/21.
//  Copyright © 2017年 WangPU. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^BlockHandle)(void);
@interface Handler : NSObject
@property (copy)BlockHandle cleanUP;
@end
