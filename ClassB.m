//
//  ClassB.m
//  BlockLearn
//
//  Created by WangPu on 2017/5/21.
//  Copyright © 2017年 WangPU. All rights reserved.
//

#import "ClassB.h"
@implementation ClassB

-(instancetype)init{

    self=[super init ];
    
    if (self) {
        _hand=[Handler new];
        _logger=[Logger new];
    }

    return self;
}

-(void)pring{

    //__weak ClassB * jj=self;
    _hand.cleanUP=^{ [_logger wright];};


}


-(void)pring2{
    
    __weak ClassB * jj=self;
    
    _hand.cleanUP=^{
        __strong ClassB * UU=jj;
        [UU.logger wright];
    };
    
    _hand.cleanUP();
    
}

-(void)dealloc{

    NSLog(@"_____3fdsfsd");

}
@end
