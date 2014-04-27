using System.Web.Mvc;
using Domain.Model.Kohde;
using Infrastructure.Repositories;

namespace PresentationLayer.Controllers
{   
    public class KohteetController : Controller
    {
		private readonly IKohdeRepository _kohdeRepository;

        public KohteetController() : this(new KohdeRepository()) { }

        // Dependency Injection TDD:tä varten
        public KohteetController(IKohdeRepository kohdeRepository)
        {
			_kohdeRepository = kohdeRepository;
        }

        #region Actions

        // GET: /Kohteet/Kohdelista
        public ViewResult Kohdelista()
        {
            return View(_kohdeRepository.All);
        }

        // GET: /Kohteet/Tiedot/5
        public ViewResult Tiedot(int id)
        {
            return View(_kohdeRepository.Find(id));
        }

        // GET: /Kohteet/Uusi
        public ActionResult Uusi()
        {
            return View();
        } 

        // POST: /Kohteet/Uusi
        [HttpPost]
        public ActionResult Uusi(Kohde kohde)
        {
            if (ModelState.IsValid) {
                _kohdeRepository.InsertOrUpdate(kohde);
                _kohdeRepository.Save();
                return RedirectToAction("Kohdelista");
            }
            return View();
        }

        // GET: /Kohteet/Muokkaa/5
        public ActionResult Muokkaa(int id)
        {
             return View(_kohdeRepository.Find(id));
        }

        // POST: /Kohteet/Muokkaa/5
        [HttpPost]
        public ActionResult Muokkaa(Kohde kohde)
        {
            if (ModelState.IsValid) {
                _kohdeRepository.InsertOrUpdate(kohde);
                _kohdeRepository.Save();
                return RedirectToAction("Kohdelista");
            }
            return View();
        }

        // GET: /Kohteet/Poista/5 
        public ActionResult Poista(int id)
        {
            return View(_kohdeRepository.Find(id));
        }

        // POST: /Kohteet/Poista/5
        [HttpPost, ActionName("Poista")]
        public ActionResult DeleteConfirmed(int id)
        {
            _kohdeRepository.Delete(id);
            _kohdeRepository.Save();

            return RedirectToAction("Kohdelista");
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing) {
                _kohdeRepository.Dispose();
            }
            base.Dispose(disposing);
        }

        #endregion Actions

    }
}

