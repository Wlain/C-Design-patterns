# [Cpp Design Patterns:C++ 设计模式](https://wlain.github.io/cppDesignPatterns/README.html)

## 设计模式的分类：

* 创建型模式（Creational Patterns）：将对象的部分创建工作延迟到子类或者其他对象，从而应对需求变化为对象创建时具体类型实现引来的冲击。
    * 单例模式（Singleton Pattern）
    * 抽象工厂模式（Abstract factory Pattern）
    * 建造者模式（Builder Pattern）
    * 工厂方法模式（Factory Method Pattern）
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

## 单例模式（Singleton Pattern）

### 目的：确保在任何时间点都只存在一个类的一个实例

* 单例设计模式确保一个类只有一个实例，并提供对该实例的全局访问点。当恰好一个对象需要在整个系统中协调动作时，就很有用，比如log
* 单例设计模式只不过是指定一个生命周期

### 设计细节

* 私有构造函数
* 删除了复制构造函数和复制赋值运算符
* 静态对象创建和静态访问方法

### 单例设计模式的好处

* 单例设计模式对应用程序配置很有帮助，因为配置可能需要全局访问，并且未来对应用程序配置的扩展可以在一个地方合并
* 此类的第二个常见用途是更新旧代码以在新架构中工作。由于开发人员可能已经自由地使用了全局变量，因此将它们移动到单个类中并使其成为单例，可能是将程序内联到更强大的面向对象结构的中间步骤
* 单例设计模式还增强了可维护性，因为它提供了对特定实例的单点访问

### 单例设计模式的弊端

* 单例对象在应用程序的整个生命周期内保持状态
* 单例对象导致代码紧密耦合
* 多线程下需要加锁，性能会降低

### 什么时候应该使用单例设计模式？

* Singleton 用于硬件接口使用限制
* 单例设计模式也广泛用于管理配置或属性文件以管理访问
* 可以将缓存用作单例对象，因为它可以具有全局引用点，并且对于将来对缓存对象的所有调用，客户端应用程序将使用内存中的对象

## 抽象工厂模式（Abstract factory Pattern）/ 工厂方法模式（Factory Method Pattern）

### 目的：用于创建批量对象

* 不允许使用构造函数并强制用户使用静态方法,私有构造函数和静态方法

### 工厂设计模式的好处

* 用于不同对象创建的单点/类，因此易于维护和理解软件
* 可以使用抽象工厂在不知道其类型的情况下创建对象
* 它提供了很好的模块化
* 允许更轻松地更改应用程序的设计，这称为松散耦合

## 建造者模式（Builder Pattern）

### 目的：用于分段创建对象

* 当我们想要构造一个复杂的对象时，使用构建器设计模式。但是，我们不希望有一个复杂的构造函数成员或需要许多参数的构造函数成员。
* Builder 设计模式一步一步地构造一个复杂的对象，最后一步将返回该对象。构造对象的过程应该是通用的，以便它可以在各种方法的帮助下用于创建同一对象的不同表示

### 建造者设计模式的好处

* 在构建器模式中，代码行数至少增加了一倍。但是在设计灵活性、更少或没有构造函数的参数以及更易读的代码方面，付出的努力得到了回报
* Builder 设计模式还有助于最小化构造函数中的参数数量，因此不需要将 null 传递给构造函数的可选参数
* 可以在对象构建过程中构建不可变对象，而无需太多复杂的逻辑
* 将构造与 对象表示分离 使对象表示切片和精确。将构建器实体分开提供了创建和实例化不同对象表示的灵活性

### 什么时候应该使用构建器设计模式？

* 每当创建新对象需要设置许多参数时，其中一些（或全部）是可选的

### 为什么我们在实现Builder设计模式时需要一个Builder类？

* 这不是必需的，但这样做有一些好处:
    * 根据 SRP，构建对象的关注点应该在单独的实体中
    * 原始对象不会膨胀
    * 简单且可维护的代码
    * 测试和理解具有许多输入参数的构造函数变得更加复杂

### Builder设计模式的最大优势

不使用建造者模式:

   ``` C++
   auto o = new MyClass(5, 5.5, 'A', var, 1000, obj9, "hello");
   ```

使用建造者模式:

   ``` C++
   auto o = MyClass.builder().a(5).b(5.5).c('A').d(var).e(1000).f(obj9).g("hello");
   ```

使用使用建造者之后，获得更具表现力的代码，可以查看哪个数据成员被分配了什么，甚至可以更改分配顺序

### 抽象工厂和构建器设计模式有什么区别？

* Factory 批量生产对象，这些对象可以是继承层次结构中的任何对象（如 Point、Point2D、Point3D）。
* 虽然 Builder 处理仅限于单个对象的对象的实例化。您会看到 Factory 是关于批量对象创建的，而构建器是分段对象创建的。
* 在这两种模式中，您都可以在其他类中分离出与对象创建相关的机制

## 原型设计模式（Prototype Pattern）

### 目的：在已经构造或预初始化的存储对象的帮助下，以较低的成本创建新对象

* 原型提供了廉价创建复杂对象的灵活性
* 现有对象充当原型，新复制的对象仅在需要时才可以更改相同的属性
* 原型是一个你复制的部分或完全初始化的对象

### 原型设计模式的好处

* 当对象实例化很费性能时，原型很有用
* 原型提供了创建高度动态系统的灵活性
* 可以通过更方便地生成复杂对象来简化系统
* 原型设计模式有助于在不知道对象类型的情况下创建对象的副本

### 使用原型设计模式有什么意义？

* 可以在 clone 预配置对象的基础上快速创建对象
* 有助于删除一堆冗余代码
* 在不知道其类型的情况下处理对象时更方便
* 当您使用命令设计模式时，原型设计模式是一个明显的选择

## 适配器模式（Adapter Pattern）

### 目的：从你拥有的接口中得到你想要的接口

* 适配器允许两个不兼容的类一起工作，方法是将一个类的接口转换为客户端/API 用户期望的接口而不更改它们。基本上，添加中间类即适配器

### 适配器设计模式的好处

* 开闭原则：适配器模式的一个优点是您不需要更改现有的类或接口,通过引入一个新类，它充当接口和类之间的适配器，您可以避免对现有代码进行任何更改
* 并避免了其他组件或应用程序中的任何更改和副作用
* 遵循单一责任原则,需要更少的维护、学习曲线和测试。
* 遵循依赖倒置原则,保持多个版本之间的二进制兼容性

### 什么时候使用适配器设计模式？

* 当你想使用一些现有的类时使用适配器类，但它的接口与你的其余代码不兼容
* 当您想要重用几个现有的子类时，这些子类缺少一些无法添加到超类的通用功能

### stl中使用适配器设计模式的例子

* stack、queue 和 priority_queue 是来自 deque 和 vector 的适配器，当堆栈执行 stack :: push () 时，底层向量执行 vector :: push_back ()。

### 生活中使用适配器的例子

* 读卡器，充当存储卡和笔记本电脑之间的适配器
* 手机和笔记本电脑充电器是一种适配器，可将标准电压和电流转换为您的设备所需的电压

### 桥接和适配器设计模式有什么区别？

* 适配器通常与现有应用程序一起使用，以使一些原本不兼容的类很好地协同工作
* Bridge 通常是预先设计的，可以独立开发应用程序的各个部分

### 装饰器和适配器设计模式有什么区别？

* 适配器将一个接口转换为另一个接口，而不添加其他功能
* 装饰器将新功能添加到现有接口中

### 代理和适配器设计模式有什么区别？

* 适配器设计模式将一个类的接口转换为兼容但不同的接口
* 代理提供相同但简单的界面，或者有时充当唯一的包装器

## 桥接模式（Bridge Pattern）

### 目的：用于将一个类解耦为两部分——抽象

* 它的实现（两者都可以独立开发，促进了类抽象与其实现之间的松散耦合）
* 通过灵活的抽象使用聚合/组合将组件连接在一起（not 继承/泛化）
* 充当桥梁的接口,使得具体类的功能独立于接口实现类,两种类型的类都可以在结构上改变而不会相互影响

### 桥接设计模式的好处

* 桥接设计模式为独立开发抽象（即接口）和实现提供了灵活性, 并且客户端/API 用户代码只能访问抽象部分，而无需关心实现部分。
* 它保留了开闭原则，换句话说，提高了可扩展性（因为客户端/API 用户代码仅依赖于抽象，因此实现可以随时修改或扩充）
* 通过使用PIMPL形式的桥接设计模式。我们可以向客户端隐藏实现细节
* 桥接设计模式是旧建议的应用，“更喜欢组合而不是继承”，但以更智能的方式
* 应避免抽象与其实现之间的编译时绑定。这样一个实现可以在运行时选择

### 桥接设计模式的实际用例是什么？

* 任何互联网浏览器中的插件都直接利用这种模式，其中浏览器仅指定抽象和实现因不同类型的插件而异

### 何时使用桥接设计模式？

* 当您不确定实施或其变体时，您仍想继续开发
* 在行为排列问题的情况下，即笛卡尔积复杂性爆炸

### 适配器和桥接设计模式有什么区别?

* 适配器通常与现有应用程序一起使用，以使一些原本不兼容的类很好地协同工作
* 桥接模式通常是预先设计的，让您可以独立开发应用程序的各个部分

### 策略和桥梁设计模式有什么区别？

* 策略是一个单维问题，如多头螺丝刀
* 桥梁是一个多维问题，如通信类型和设备

## 外观设计模式（Facade Pattern）

### 目的：通过隐藏系统复杂性来提供统一的接口，用于为复杂系统提供统一的接口（包了一层接口，提供更简单的调用）

* 通过提供单一简化的API屏蔽与更复杂组件的交互，提高软件库的可读性和可用性
* 为更通用的功能提供特定于上下文的接口。
* 作为更广泛的单体或紧密耦合系统重构的起点，以支持更松散耦合的代码
* 外观设计模式就是在大量复杂的代码上提供一个简单易懂的界面

### 外观模式设计模式的好处

* 外观模式定义了一个更高级别的接口，它通过包装一个复杂的子系统使子系统更易于使用
    * 这减少了成功利用子系统所需的学习曲线

### Facade是一个包含很多其他类的类吗？

* 是的。它是应用程序中许多子系统的包装器。

### 外观设计模式的实际用例是什么？

* 外观设计模式的一个典型应用是控制台/终端/命令提示符

### 适配器和外观设计模式之间的区别？

* Adapter 封装了一个类，Facade 可以代表多个类

## 模板方法模式（Template Method Pattern）

### 目的：通过继承的方式，给继承者提供框架

* 算法一般可以分解为通用部分（即高级部分）以及细节部分,策略设计模式为我们非常有效地处理了这些问题

### 模板方法设计模式的好处

* 如果你有一个单一的算法暴露给每个类。当该算法的步骤发生变化时，您可能需要修改所有类，但是，如果您有几个类包含几乎相同的算法，但有一些细微差别，并且使用了模板方法设计模式。那么你就没有后顾之忧了
* 通过将通用步骤拉入抽象类，您可以限制代码的重复性并鼓励代码的表现力

### 策略和模板方法设计模式有什么区别？

* 模板方法基于继承，它通过在派生类中扩展算法的部分来改变算法的部分
* 策略基于组合，该组合通过向对象提供对应于不同行为的不同策略来改变对象的部分行为
* 模板方法在类级别工作，因此它是静态的
* 策略在对象级别起作用，让您在运行时切换行为

### 我们应该在哪里使用模板方法设计模式？

* 当您想让客户只扩展算法的特定步骤而不是整个算法结构时，可以使用模板方法设计模式

## 命令模式（Command Pattern）

### 目的：

* 通过为一组操作创建一个单独的对象来**解耦**发送者和接收者
* 行为设计模式处理对象之间的职责分配，从而使对象之间的交互变得容易且松散耦合
* 命令设计模式是一个非常简单的表示指令或指令集的对象，有助于支持可撤销操作和查询/请求定制
* 命令和查询的关系：
    * 命令：请求操作或更改，例如重命名文件。
    * 查询：询问信息（不会导致任何突变）例如列出当前目录中的所有文件

### 命令设计模式的好处

* 命令设计模式将操作数和操作解耦。因此便于扩展添加新命令很容易并且无需更改现有代码
* 通过排队命令，您还可以像我们上面所做的那样在系统中定义回滚功能
* 它还允许我们创建一个带有一堆命令的宏，这些命令可以在一次调用中一起触发
* 由于命令设计模式有一个单独的结构来存储一组操作，我们可以利用它来安排它

### 命令设计模式的重要方面是什么？

* 接口分离：invoker 与 receiver 是隔离的
* 时间分离：存储一组可以调度的准备就绪的指令

### 使用命令设计模式背后的原因是什么？

* 解耦命令的发送者和接收者
* 实现回调机制
* 实现撤销和重做功能
* 维护命令历史

### 命令设计模式和备忘录设计模式之间的区别？

* 命令设计模式表示请求令牌备忘录设计模式表示对象在特定时间的内部状态多态性
* 多态性对对命令设计模式很重要，但对备忘录设计模式不重要

## 访问者模式（Visitor Pattern）

### 目的：在一组相似类型的对象或层次结构上定义新操作

* 经典的访问者设计模式有一些访问者组件，允许遍历整个继承结构，但在此之前， 必须执行一次visit()，在整个层次结构中调用的单个方法。
* 访问者设计模式符合单一职责，和开闭原则。

### 访问者设计模式的好处

* 复合单一职责原则意味着在单独的实体/类中分离特性类型的逻辑。在以上例子中， DocumentPrinter只处理不同文档类型的打印。
* 符合开闭原则，一旦我们为层次结构插入方法，就可以在不触及任何类头的情况下添加新功能visit()
* 当已经对整个层次结构进行了单元测试时，这会非常有用。
* 访问者模式性能优于 dynamic_cast、 typeid ()并检查枚举/字符串比较

### 什么时候应该使用访问者设计模式？

当需求不断变化时，访问者设计模式非常有用，这也会影响继承层次结构中的多个类

### 访问者设计模式的典型用例是什么？

* 代替dynamic_cast<>,typeid()等
* 处理不同类型对象的集合
* 从集合中过滤不同类型的对象

### 访问者与装饰者设计模式之间的区别？

* 装饰器（结构设计模式）通过增强现有功能来处理对象。
* 访问者（行为设计模式）适用于希望根据具体类型运行不同方法但避免 dynamic_cast<>() 或 typeof() 运算符的类层次结构
