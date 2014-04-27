using System;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Linq.Expressions;
using DataLayer.Models;
using Domain.Model.Kohde;

namespace Infrastructure.Repositories
{
    public class KohdeRepository : IKohdeRepository
    {
        readonly KohdeContext _context = new KohdeContext();

        public IQueryable<Kohde> All
        {
            get { return _context.Kohteet; }
        }

        public IQueryable<Kohde> AllIncluding(params Expression<Func<Kohde, object>>[] includeProperties)
        {
            IQueryable<Kohde> query = _context.Kohteet;
            foreach (var includeProperty in includeProperties) {
                query = query.Include(includeProperty);
            }
            return query;
        }

        public Kohde Find(int id)
        {
            return _context.Kohteet.Find(id);
        }

        public void InsertOrUpdate(Kohde kohde)
        {
            if (kohde.Id == default(int)) {
                // New entity
                _context.Kohteet.Add(kohde);
            } else {
                // Existing entity
                _context.Entry(kohde).State = EntityState.Modified;
            }
        }

        public void Delete(int id)
        {
            var kohde = _context.Kohteet.Find(id);
            _context.Kohteet.Remove(kohde);
        }

        public void Save()
        {
            _context.SaveChanges();
        }

        public void Dispose() 
        {
            _context.Dispose();
        }
    }
}