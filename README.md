# Cpp Design Patterns:C++ 设计模式

## 设计模式的分类：
* 创建型模式（Creational Patterns）：将对象的部分创建工作延迟到子类或者其他对象，从而应对需求变化为对象创建时具体类型实现引来的冲击。
  * 单例模式（Singleton Pattern）
  * 抽象工程模式（Abstract factory Pattern）
  * 建造者模式（Builder Pattern）
  * 工程方法模式（Factory Method Pattern）
  * 原型模式（Prototype Pattern）
* 结构型模式（Structural Patterns）：通过类继承或者对象组合获得更灵活的结构，从而应对需求变化为对象的结构带来的冲击。 
  * 适配器模式（Adapter Pattern）
  * 桥接模式（Bridge Pattern）
  * 装饰者模式（decoration Pattern）
  * 组合模式（Composite Pattern）
  * 外观模式（Facade Pattern）
  * 享元模式（Flyweight Pattern）
  * 代理模式（Proxy Pattern）
* 行为型模式（Behavioral Patterns）：通过类继承或者对象组合来划分类与对象间的职责，从而应对需求变化为多个交互的对象带来的冲击。
  * 模板方法模式（Template Method Pattern）
  * 命令模式（Command Pattern）
  * 迭代器模式（Iterator Pattern）
  * 观察者模式（Observer Pattern）
  * 中介者模式（Mediator Pattern）
  * 备忘录模式（Memento Pattern）
  * 解释器模式（Interpreter Pattern）
  * 状态模式（State Pattern）
  * 策略模式（Strategy Pattern）
  * 职责链模式（Chain of Responsibility Pattern）
  * 访问者模式（Visitor Pattern）
## 遇到问题的一般思路
* 分解：即分而治之，将大问题分解为多个小问题，将复杂问题分解为多个简单问题。
* 抽象：抽象是一种能让你在关注某一概念的同时可以放心地忽略其中一些细节的能力——在不同的层次处理不同的细节

## 重构思路
* 静态 → 动态 
* 早绑定 → 晚绑定 
* 继承 → 组合 
* 编译时依赖 → 运行时依赖 
* 紧耦合 → 松耦合

## 面向对象设计八大原则
* 一、依赖倒置原则（DIP）
  * 高层模块(稳定)不应该依赖于低层模块(变化)，二者都应该依赖于抽象(稳定) 
  * 抽象(稳定)不应该依赖于实现细节(变化) ，实现细节应该依赖于抽象(稳定)
* 二、开放封闭原则（OCP） 
  * 对扩展开放，对更改封闭
  * 类模块应该是可扩展的，但是不可修改
* 三、单一职责原则（SRP） 
  * 一个类应该仅有一个引起它变化的原因
  * 变化的方向隐含着类的责任
* 四、Liskov 替换原则（LSP） 
  * 子类必须能够替换它们的基类(IS-A)
  * 继承表达类型抽象 
* 五、接口隔离原则（ISP） 
  * 不应该强迫客户程序依赖它们不用的方法 
  * 接口应该小而完备 
* 六、优先使用对象组合，而不是类继承 
  * 类继承通常为“白箱复用”，对象组合通常为“黑箱复用” 
  * 继承在某种程度上破坏了封装性，子类父类耦合度高 
  * 而对象组合则只要求被组合的对象具有良好定义的接口，耦合度低。 
* 七、封装变化点 
  * 使用封装来创建对象之间的分界层，让设计者可以在分界层的一侧进行修改，而不会对另一侧产生不良的影响，从而实现层次间的松耦合。
* 八、针对接口编程，而不是针对实现编程 
  * 不将变量类型声明为某个特定的具体类，而是声明为某个接口
  * 客户程序无需获知对象的具体类型，只需要知道对象所具有的接口   
  * 减少系统中各部分的依赖关系，从而实现“高内聚、松耦合”的类型设计方案