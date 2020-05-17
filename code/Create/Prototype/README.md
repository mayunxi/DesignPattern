原型模式提供了自我复制的功能，就是说新对象的创建可以通过已有对象进行创建。

定义：用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。 其实就是从一个对象复制另一个对象而不需要知道任何复制的细节

UML图：


![图片.png](https://upload-images.jianshu.io/upload_images/21440240-e3a2904812a0d231.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



### 优缺点：
优点：复制自身。客户不知道需要对象的实际类型，只需知道它的抽象基类即可。(即有继承树的情况)
缺点：必须先有一个对象实例(即原型)才能clone。

 C++没有克隆方法，要克隆一个对象，需要借助拷贝构造函数（Copy Constructor）来实现。
```
    #include <cstdio>
    //代码来自http://blog.csdn.net/cabinriver/article/details/8895372
    //接口
    class CPrototype
    {
    public:
    	CPrototype(){}
    	virtual ~CPrototype(){}
    	virtual CPrototype* Clone() = 0;
    };

    //实现
    class CConcretePrototype : public CPrototype
    {
    public:
    	CConcretePrototype():m_counter(0){}
    	virtual ~CConcretePrototype(){}
    	//拷贝构造函数
    	CConcretePrototype(const CConcretePrototype& rhs)
    	{
    		m_counter = rhs.m_counter;
    	}

    	//复制自身
    	virtual CPrototype* Clone()
    	{
    		//调用拷贝构造函数
    		return new CConcretePrototype(*this);
    	}
    private:
    	int m_counter;
    };

    int main(int argc, char **argv)
    {
    	//生成对像
    	CPrototype* conProA = new CConcretePrototype();
    	//复制自身
    	CPrototype* conProB = conProA->Clone();
    	delete conProA; conProA=NULL;
    	delete conProB; conProB=NULL;
    	return 0;
    }
```

原型模式中需要特别注意的问题是深拷贝 浅拷贝问题 。   上面代码不涉及深拷贝 ，深拷贝即把用到的指针和引用所指向的对象一起进行复制。


### 关于原型模式的讨论
原型模式通过复制原型（原型）而获得新对象创建的功能，这里原型本身就是"对象工厂"（因为能够生产对象），实际上原型模式和 Builder 模式、AbstractFactory 模式都是通过一个类（对象实例）来专门负责对象的创建工作（工厂对象），它们之间的区别是： Builder 模式重在复杂对象的一步步创建（并不直接返回对象），AbstractFactory 模式重在产生多个相互依赖类的对象，而原型模式重在从自身复制自己创建新类。
