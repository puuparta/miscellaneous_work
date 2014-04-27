using System;
using System.Collections.Generic;
using Infrastructure;

namespace NHibernateDemo
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            var notificationService = new NotificationRepository();
            var notifications = notificationService.GetAll();
            foreach (var notification in notifications)
            {
                Console.WriteLine("\n\rNOTIFICATION:{0}", notification.FirstName);
                foreach (var field in notification.NotificationFields)
                {
                    Console.WriteLine("\tFIELD:{0}", field.Fieldname);
                }
            }
        }
    }

    public interface IDataContext : IDisposable
    {
        // Query services
        IList<T> GetAll<T>() where T : class, new();
        IList<T> GetAll<T>(int pageIndex, int pageSize) where T : class, new();
        //IList<T> GetByCriteria<T>(System.Data.Query query) where T : class, new();
        //IList<T> GetByCriteria<T>(System.Data.Query query, int index, int size) where T : class, new();
        T GetByID<T>(object id) where T : class, new();
        int GetCount<T>();
        //int GetCount<T>(System.Data.Query query);
        // CRUD services (well, mostly CUD)
        void Add(object item);
        void Delete(object item);
        void Save(object item);
        // Transaction management
        bool IsInTransaction { get; }
        bool IsDirty { get; }
        void BeginTransaction();
        void Commit();
        void Rollback();
    }

    public interface IDataMapper<T>
    {
        // Persistence
        void Create(T item);
        void Update(T item);
        void Delete(T item);
        // Repository
        IList<T> GetAll();
        IList<T> GetAll(int index, int size);
        int GetCount();
        
    }
    public abstract class BaseDataContext : IDataContext
    {
        // Define a placeholder for methods that return a data mapper
        protected abstract IDataMapper<T> GetDataMapper<T>();
        protected abstract IDataMapper<T> GetDataMapper(Type t);
        //protected abstract IDataMapper<T> GetDataMapper<T>() where T : class, new();

        public void Add(object item)
        {
            Type t = item.GetType();
            GetDataMapper(t).Create(item);
        }
        public void Delete(object item)
        {
            Type t = item.GetType();
            GetDataMapper(t).Delete(item);
        }
        public void Save(object item)
        {
            Type t = item.GetType();
            GetDataMapper(t).Update(item);
        }

      

        public void Dispose()
        {
            throw new NotImplementedException();
        }

        public IList<T> GetAll<T>() where T : class, new()
        {
            return GetDataMapper<T>().GetAll();
        }
        public IList<T> GetAll<T>(int index, int size) where T : class, new()
        {
            return GetDataMapper<T>().GetAll(index, size);
        }

       

        public T GetByID<T>(object id) where T : class, new()
        {
            throw new NotImplementedException();
        }

        public int GetCount<T>()
        {
            throw new NotImplementedException();
        }

       


        public bool IsInTransaction { get; private set; }
        public bool IsDirty { get; private set; }
        public void BeginTransaction()
        {
            throw new NotImplementedException();
        }

        public void Commit()
        {
            throw new NotImplementedException();
        }

        public void Rollback()
        {
            throw new NotImplementedException();
        }
    }


}