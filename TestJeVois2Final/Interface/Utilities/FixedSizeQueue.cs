﻿using System;
using System.Collections.Concurrent;

namespace Utilities
{
    public class FixedSizedQueue<T> : ConcurrentQueue<T>
    {
        private readonly object syncObject = new object();

        public int Size { get; private set; }

        public FixedSizedQueue(int size)
        {
            Size = size;
        }

        public new void Enqueue(T obj)
        {
            base.Enqueue(obj);
            lock (syncObject)
            {
                while (base.Count > Size)
                {
                    T outObj;
                    base.TryDequeue(out outObj);
                }
            }
        }

        public new T Peek()
        {
            lock (syncObject)
            {
                T outObj;
                base.TryPeek(out outObj);
                return outObj;
            }
        }

        public new T DeQueue()
        {
            lock (syncObject)
            {
                T outObj;
                base.TryDequeue(out outObj);
                return outObj;
            }
        }
    }
}
