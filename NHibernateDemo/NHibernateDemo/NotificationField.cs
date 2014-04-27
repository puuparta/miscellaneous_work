using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NHibernateDemo
{
    public class NotificationField :INotificationField
    {
        public virtual int Id { get; set; }
        public virtual int NotificationId { get; set; }
        public virtual string Fieldname { get; set; }
    }
}
