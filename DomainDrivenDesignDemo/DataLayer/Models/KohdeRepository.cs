using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Linq.Expressions;
using System.Web;
using Domain.Model.Kohde;

namespace DataLayer.Models
{
    public class KohdeRepository : IKohdeRepository
    {
        KohdeContext context = new KohdeContext();

        public IQueryable<Kohde> All
        {
            get { return context.Kohteet; }
        }

        public IQueryable<Kohde> AllIncluding(params Expression<Func<Kohde, object>>[] includeProperties)
        {
            IQueryable<Kohde> query = context.Kohteet;
            foreach (var includeProperty in includeProperties) {
                query = query.Include(includeProperty);
            }
            return query;
        }

        public Kohde Find(int id)
        {
            return context.Kohteet.Find(id);
        }

        public void InsertOrUpdate(Kohde kohde)
        {
            if (kohde.Id == default(int)) {
                // New entity
                context.Kohteet.Add(kohde);
            } else {
                // Existing entity
                context.Entry(kohde).State = EntityState.Modified;
            }
        }

        public void Delete(int id)
        {
            var kohde = context.Kohteet.Find(id);
            context.Kohteet.Remove(kohde);
        }

        public void Save()
        {
            context.SaveChanges();
        }

        public void Dispose() 
        {
            context.Dispose();
        }
    }
}