using System.Collections.Generic;

namespace Domain
{
    public interface IRepository<T>
    {
        IList<T> GetAll();
    }
}