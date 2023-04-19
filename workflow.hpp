/***
 * MIT License
 * Copyright 2023 Mountcloud mountcloud@outlook.com
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __WORKFLOW_HPP__
#define __WORKFLOW_HPP__

#include <functional>
#include <vector>
namespace mc::workflow{

    /// @brief 工作节点接口
    template<typename InData>
    class IWorkNode{
    public:
        /// @brief 执行工作
        virtual void run(InData idata) = 0;
    };

    /// @brief 具有校验条件的Next
    template<typename OutData>
    class ConditionNext{
    public:
        /// @brief 切换条件
        std::function<bool(OutData odata)> onCheck;
        /// @brief 下一个节点
        IWorkNode<OutData>* nextNode;
    };

    /// @brief 工作节点
    /// @tparam InData  输入数据类型
    /// @tparam OutData 输出数据类型
    template<typename InData,typename OutData>
    class WorkNode : public IWorkNode<InData> {
    public:
        
        
        /// @brief 需要实现的工作方法
        /// @param idata 输入数据
        /// @return 输出数据
        virtual OutData onProcess(InData idata) = 0;

        /// @brief 执行工作
        virtual void run(InData idata) override{
            OutData odata = onProcess(idata);
            onNext(odata);
        };

        /// @brief 添加条件节点（条件满足则传递）
        WorkNode* addConditionNext(std::function<bool(OutData odata)> onCheck,IWorkNode<OutData>* nextNode){
            ConditionNext<OutData> sw;
            sw.onCheck = onCheck;
            sw.nextNode = nextNode;
            conditionNexts.push_back(sw);
            return this;
        };

        /// @brief 添加普通节点（无条件传递）
        WorkNode* addNext(IWorkNode<OutData>* next){
            nexts.push_back(next);
            return this;
        };

        /// @brief 执行下一个节点
        /// @param outdata onProcess的返回值 
        void onNext(OutData outdata){
            for(auto sw : conditionNexts){
                if(sw.onCheck(outdata)){
                    sw.nextNode->run(outdata);
                }
            }
            for(auto next : nexts){
                next->run(outdata);
            }
        };
    private:
        //条件节点列表
        std::vector<ConditionNext<OutData>> conditionNexts;
        //普通节点列表
        std::vector<IWorkNode<OutData>*> nexts;
    };
}

#endif