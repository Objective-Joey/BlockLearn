//
//  DescriptionFile.h
//  BlockLearn
//
//  Created by WangPu on 2017/5/17.
//  Copyright © 2017年 WangPU. All rights reserved.
//

#ifndef DescriptionFile_h
#define DescriptionFile_h
总结《Objective-C高级编程》这本书对Block的讲述
虽然书中已经详细的讲解了Block的本质，但是本文作为狗尾续貂，给新手一个快速入坑的途径。
Block：带有局部变量的匿名函数
为了看到编译后的Block语法源码，请在终端中输入 clang -rewrite-objc ClassA.m
将Block语法源码转换为C++的源代码，说是C++，其实也仅使用了struct结构，其本质是C语言源代码。

问题一：被__block修饰与没有被修饰的局部变量被编译为C++源码的区别
答：被__block修饰的局部变量会被编译为结构体，该结构体持有局部变量，blcok具有指向该结构体的指针。而没有被修饰的局部变量则直接被block结构体作为结构体成员拥有。
问题二：Block的存储域？
答：Blcok常见为三类，NSConcreteStackBlock／NSConcreteGlobalBlock／NSConcreteMallocBlock。如果Block声明为全局变量或者表达式中不带有截获的局部变量，则Block为NSConcreteGlobalBlock类的对象且设置在数据区域。除此之外Block都是NSConcreteStackBlock类的对象且设置在栈上。Block为NSConcreteStackBlock类的对象在调用copy方法后成NSConcreteMallocBlock类的对象且设置在堆上。然而不管Block配置在何处，Block使用Copy方法复制都不会引起任何问题。
问题三：__block变量存储域。
答：前面说过，__block修饰的局部变量会被编译成结构体。__block修饰的局部变量会随Block复制到堆上也复制到堆上。
问题四：被Block截获的对象变量如何被复制到堆上又如何被释放？
答：Block会生成Copy方法和depose方法（相当于delloc），在Block复制到堆上的时候调用copy，销毁时调用depose。
问题五：破除循环引用。
答：使用__weak修饰局部变量。这样Block持有截获的对象的弱引用，当被引用对象为空时，Block截获局部变量置为null。
问题六：MRC下的Block内存管理。
答：当Blcok被复制到堆上，就可以retain／release，和普通对象没有差异。最重要一点。被__block修饰的对象类型的自动变量不会被retain。反之，没有被__block修饰的对象型局部变量会被retain。这时候使用__block就同ARC下使用__weak来破除循环引用一样。
问题七：写在Block表达式里面的局部变量在Block语法下是怎样的？
答：直接在Block表达式定义，就是局部变量，没什么特别的。


typedef void(*BlockTest) (void);

// @implementation ClassA

//__block修饰的局部变量
struct __Block_byref_arr1_0 {
    void *__isa;
    __Block_byref_arr1_0 *__forwarding;
    int __flags;
    int __size;
    void (*__Block_byref_id_object_copy)(void*, void*);
    void (*__Block_byref_id_object_dispose)(void*);
    NSMutableArray *arr1;
};

struct __ClassA__Test_block_impl_0 {
    struct __block_impl impl;
    struct __ClassA__Test_block_desc_0* Desc;
    NSMutableArray *arr2;//没用__block修饰的局部变量
    __Block_byref_arr1_0 *arr1; // by ref
    __ClassA__Test_block_impl_0(void *fp, struct __ClassA__Test_block_desc_0 *desc, NSMutableArray *_arr2, __Block_byref_arr1_0 *_arr1, int flags=0) : arr2(_arr2), arr1(_arr1->__forwarding) {
        impl.isa = &_NSConcreteStackBlock;
        impl.Flags = flags;
        impl.FuncPtr = fp;
        Desc = desc;
    }
};
//Block指向的函数
static void __ClassA__Test_block_func_0(struct __ClassA__Test_block_impl_0 *__cself) {
    __Block_byref_arr1_0 *arr1 = __cself->arr1; // bound by ref
    NSMutableArray *arr2 = __cself->arr2; // bound by copy
    
    
    int a=9;//直接定义
    NSArray * arr=((NSArray *(*)(id, SEL, ObjectType, ...))(void *)objc_msgSend)((id)((NSArray *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSArray"), sel_registerName("alloc")), sel_registerName("initWithObjects:"), (id)(NSString *)&__NSConstantStringImpl__var_folders_2s_n_67nh492zx2s8_x2yy0ffjc0000gn_T_ClassA_5fa497_mi_0, __null);
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2s_n_67nh492zx2s8_x2yy0ffjc0000gn_T_ClassA_5fa497_mi_1,(arr1->__forwarding->arr1),arr2);
    
}
//copy
static void __ClassA__Test_block_copy_0(struct __ClassA__Test_block_impl_0*dst, struct __ClassA__Test_block_impl_0*src) {_Block_object_assign((void*)&dst->arr1, (void*)src->arr1, 8/*BLOCK_FIELD_IS_BYREF*/);_Block_object_assign((void*)&dst->arr2, (void*)src->arr2, 3/*BLOCK_FIELD_IS_OBJECT*/);}
//depose
static void __ClassA__Test_block_dispose_0(struct __ClassA__Test_block_impl_0*src) {_Block_object_dispose((void*)src->arr1, 8/*BLOCK_FIELD_IS_BYREF*/);_Block_object_dispose((void*)src->arr2, 3/*BLOCK_FIELD_IS_OBJECT*/);}

static struct __ClassA__Test_block_desc_0 {
    size_t reserved;
    size_t Block_size;
    void (*copy)(struct __ClassA__Test_block_impl_0*, struct __ClassA__Test_block_impl_0*);
    void (*dispose)(struct __ClassA__Test_block_impl_0*);
} __ClassA__Test_block_desc_0_DATA = { 0, sizeof(struct __ClassA__Test_block_impl_0), __ClassA__Test_block_copy_0, __ClassA__Test_block_dispose_0};

struct __ClassA__Test_block_impl_1 {
    struct __block_impl impl;
    struct __ClassA__Test_block_desc_1* Desc;
    NSMutableArray *arr2;
    __Block_byref_arr1_0 *arr1; // by ref
    __ClassA__Test_block_impl_1(void *fp, struct __ClassA__Test_block_desc_1 *desc, NSMutableArray *_arr2, __Block_byref_arr1_0 *_arr1, int flags=0) : arr2(_arr2), arr1(_arr1->__forwarding) {
        impl.isa = &_NSConcreteStackBlock;
        impl.Flags = flags;
        impl.FuncPtr = fp;
        Desc = desc;
    }
};
static void __ClassA__Test_block_func_1(struct __ClassA__Test_block_impl_1 *__cself) {
    __Block_byref_arr1_0 *arr1 = __cself->arr1; // bound by ref
    NSMutableArray *arr2 = __cself->arr2; // bound by copy
    
    
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2s_n_67nh492zx2s8_x2yy0ffjc0000gn_T_ClassA_5fa497_mi_2,(arr1->__forwarding->arr1),arr2);
    
}
static void __ClassA__Test_block_copy_1(struct __ClassA__Test_block_impl_1*dst, struct __ClassA__Test_block_impl_1*src) {_Block_object_assign((void*)&dst->arr1, (void*)src->arr1, 8/*BLOCK_FIELD_IS_BYREF*/);_Block_object_assign((void*)&dst->arr2, (void*)src->arr2, 3/*BLOCK_FIELD_IS_OBJECT*/);}

static void __ClassA__Test_block_dispose_1(struct __ClassA__Test_block_impl_1*src) {_Block_object_dispose((void*)src->arr1, 8/*BLOCK_FIELD_IS_BYREF*/);_Block_object_dispose((void*)src->arr2, 3/*BLOCK_FIELD_IS_OBJECT*/);}

static struct __ClassA__Test_block_desc_1 {
    size_t reserved;
    size_t Block_size;
    void (*copy)(struct __ClassA__Test_block_impl_1*, struct __ClassA__Test_block_impl_1*);
    void (*dispose)(struct __ClassA__Test_block_impl_1*);
} __ClassA__Test_block_desc_1_DATA = { 0, sizeof(struct __ClassA__Test_block_impl_1), __ClassA__Test_block_copy_1, __ClassA__Test_block_dispose_1};

static void _I_ClassA_Test(ClassA * self, SEL _cmd) {
    
    __attribute__((__blocks__(byref))) __Block_byref_arr1_0 arr1 = {(void*)0,(__Block_byref_arr1_0 *)&arr1, 33554432, sizeof(__Block_byref_arr1_0), __Block_byref_id_object_copy_131, __Block_byref_id_object_dispose_131, ((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSMutableArray"), sel_registerName("alloc")), sel_registerName("init"))};
    NSMutableArray *arr2=((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSMutableArray"), sel_registerName("alloc")), sel_registerName("init"));
    
    BlockTest blk =((void (*)())&__ClassA__Test_block_impl_0((void *)__ClassA__Test_block_func_0, &__ClassA__Test_block_desc_0_DATA, arr2, (__Block_byref_arr1_0 *)&arr1, 570425344));
    
    BlockTest blk2=((void (*)())&__ClassA__Test_block_impl_1((void *)__ClassA__Test_block_func_1, &__ClassA__Test_block_desc_1_DATA, arr2, (__Block_byref_arr1_0 *)&arr1, 570425344));
}


#endif /* DescriptionFile_h */
