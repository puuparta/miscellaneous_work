using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Domain.Notification;
using NHibernate.Cfg;
using NHibernate.Dialect;
using NHibernate.Driver;
using NHibernate.Linq;

namespace Infrastructure
{
    public class NotificationRepository : INotificationRepository
    {
        public IList<INotification> GetAll()
        {
            // webbikäyttöön
            // App_Start.NHibernateProfilerBootstrapper.PreStart();

            // konsolissa
            // NHibernateProfiler.Initialize();

            IList<INotification> notifications;
            var cfg = new Configuration();
            cfg.DataBaseIntegration(x =>
                {
                    x.ConnectionString = "Server=localhost;Database=NHibernateDemo;Integrated Security=SSPI;";
                    x.Driver<SqlClientDriver>();
                    x.Dialect<MsSql2008Dialect>();
                    //x.LogFormattedSql = true;
                    //x.LogSqlInConsole = true;
                });
            cfg.SessionFactory().GenerateStatistics();
            cfg.AddAssembly(Assembly.Load("Domain"));
            var sessionFactory = cfg.BuildSessionFactory();
            var session = sessionFactory.OpenSession();
            var notificationsQueryable =
                from customer in session.Query<INotification>()
                //where customer.FirstName.Contains("e")   
                orderby customer.FirstName
                select customer;
            notifications = notificationsQueryable.ToList();
            return notifications;
        }
    }
}