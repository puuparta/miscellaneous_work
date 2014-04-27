using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NHibernateDemo
{
    public class Notification : INotification
    {
        public Notification()
        {
            NotificationFields = new List<INotificationField>();
        }
        public virtual int Id { get; set; }
        public virtual string FirstName { get; set; }
        public virtual IList<INotificationField> NotificationFields { get; set; }
    }

}
